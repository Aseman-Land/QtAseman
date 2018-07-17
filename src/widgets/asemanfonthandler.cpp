/*
    Copyright (C) 2017 Aseman Team
    http://aseman.co

    AsemanQtTools is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AsemanQtTools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "asemanfonthandler.h"
#include "asemanlistrecord.h"

#include <QFont>
#include <QHash>
#include <QDebug>

#ifdef QT_WIDGETS_LIB
#include <QDialog>
#include <QFontDialog>
#include <QComboBox>
#include <QVBoxLayout>
#endif

QMap<int,QString> aseman_font_handler_scipts;

class AsemanFontHandlerPrivate
{
public:
    QVariantMap fonts;
#ifdef QT_WIDGETS_LIB
    QHash<QComboBox*, QFontDialog*> combo_hash;
    QHash<QComboBox*, QVariantMap> combo_cache;
#endif
};

AsemanFontHandler::AsemanFontHandler(QObject *parent) :
    QObject(parent)
{
    p = new AsemanFontHandlerPrivate;

    if(aseman_font_handler_scipts.isEmpty())
    {
        aseman_font_handler_scipts[QChar::Script_Unknown] = QStringLiteral("unknown");
        aseman_font_handler_scipts[QChar::Script_Inherited] = QStringLiteral("inherited");
        aseman_font_handler_scipts[QChar::Script_Common] = QStringLiteral("common");
        aseman_font_handler_scipts[QChar::Script_Latin] = QStringLiteral("latin");
        aseman_font_handler_scipts[QChar::Script_Greek] = QStringLiteral("greek");
        aseman_font_handler_scipts[QChar::Script_Cyrillic] = QStringLiteral("cyrillic");
        aseman_font_handler_scipts[QChar::Script_Armenian] = QStringLiteral("armenian");
        aseman_font_handler_scipts[QChar::Script_Hebrew] = QStringLiteral("hebrew");
        aseman_font_handler_scipts[QChar::Script_Arabic] = QStringLiteral("arabic");
        aseman_font_handler_scipts[QChar::Script_Syriac] = QStringLiteral("syriac");
        aseman_font_handler_scipts[QChar::Script_Thaana] = QStringLiteral("thaana");
        aseman_font_handler_scipts[QChar::Script_Devanagari] = QStringLiteral("devanagari");
        aseman_font_handler_scipts[QChar::Script_Bengali] = QStringLiteral("bengali");
        aseman_font_handler_scipts[QChar::Script_Gurmukhi] = QStringLiteral("gurmukhi");
        aseman_font_handler_scipts[QChar::Script_Gujarati] = QStringLiteral("gujarati");
        aseman_font_handler_scipts[QChar::Script_Oriya] = QStringLiteral("oriya");
        aseman_font_handler_scipts[QChar::Script_Tamil] = QStringLiteral("tamil");
        aseman_font_handler_scipts[QChar::Script_Telugu] = QStringLiteral("telugu");
        aseman_font_handler_scipts[QChar::Script_Kannada] = QStringLiteral("kannada");
        aseman_font_handler_scipts[QChar::Script_Malayalam] = QStringLiteral("malayalam");
        aseman_font_handler_scipts[QChar::Script_Sinhala] = QStringLiteral("sinhala");
        aseman_font_handler_scipts[QChar::Script_Thai] = QStringLiteral("thai");
        aseman_font_handler_scipts[QChar::Script_Lao] = QStringLiteral("lao");
        aseman_font_handler_scipts[QChar::Script_Tibetan] = QStringLiteral("tibetan");
        aseman_font_handler_scipts[QChar::Script_Myanmar] = QStringLiteral("myanmar");
        aseman_font_handler_scipts[QChar::Script_Georgian] = QStringLiteral("georgian");
        aseman_font_handler_scipts[QChar::Script_Hangul] = QStringLiteral("hangul");
        aseman_font_handler_scipts[QChar::Script_Ethiopic] = QStringLiteral("ethiopic");
        aseman_font_handler_scipts[QChar::Script_Cherokee] = QStringLiteral("cherokee");
        aseman_font_handler_scipts[QChar::Script_CanadianAboriginal] = QStringLiteral("canadianAboriginal");
        aseman_font_handler_scipts[QChar::Script_Ogham] = QStringLiteral("ogham");
        aseman_font_handler_scipts[QChar::Script_Runic] = QStringLiteral("runic");
        aseman_font_handler_scipts[QChar::Script_Khmer] = QStringLiteral("khmer");
        aseman_font_handler_scipts[QChar::Script_Mongolian] = QStringLiteral("mongolian");
        aseman_font_handler_scipts[QChar::Script_Hiragana] = QStringLiteral("hiragana");
        aseman_font_handler_scipts[QChar::Script_Katakana] = QStringLiteral("katakana");
        aseman_font_handler_scipts[QChar::Script_Bopomofo] = QStringLiteral("bopomofo");
        aseman_font_handler_scipts[QChar::Script_Han] = QStringLiteral("han");
        aseman_font_handler_scipts[QChar::Script_Yi] = QStringLiteral("yi");
        aseman_font_handler_scipts[QChar::Script_OldItalic] = QStringLiteral("oldItalic");
        aseman_font_handler_scipts[QChar::Script_Gothic] = QStringLiteral("gothic");
        aseman_font_handler_scipts[QChar::Script_Deseret] = QStringLiteral("deseret");
        aseman_font_handler_scipts[QChar::Script_Tagalog] = QStringLiteral("tagalog");
        aseman_font_handler_scipts[QChar::Script_Hanunoo] = QStringLiteral("hanunoo");
        aseman_font_handler_scipts[QChar::Script_Buhid] = QStringLiteral("buhid");
        aseman_font_handler_scipts[QChar::Script_Tagbanwa] = QStringLiteral("tagbanwa");
        aseman_font_handler_scipts[QChar::Script_Coptic] = QStringLiteral("coptic");
        aseman_font_handler_scipts[QChar::Script_Limbu] = QStringLiteral("limbu");
        aseman_font_handler_scipts[QChar::Script_TaiLe] = QStringLiteral("taiLe");
        aseman_font_handler_scipts[QChar::Script_LinearB] = QStringLiteral("linearB");
        aseman_font_handler_scipts[QChar::Script_Ugaritic] = QStringLiteral("ugaritic");
        aseman_font_handler_scipts[QChar::Script_Shavian] = QStringLiteral("shavian");
        aseman_font_handler_scipts[QChar::Script_Osmanya] = QStringLiteral("osmanya");
        aseman_font_handler_scipts[QChar::Script_Cypriot] = QStringLiteral("cypriot");
        aseman_font_handler_scipts[QChar::Script_Braille] = QStringLiteral("braille");
        aseman_font_handler_scipts[QChar::Script_Buginese] = QStringLiteral("buginese");
        aseman_font_handler_scipts[QChar::Script_NewTaiLue] = QStringLiteral("newTaiLue");
        aseman_font_handler_scipts[QChar::Script_Glagolitic] = QStringLiteral("glagolitic");
        aseman_font_handler_scipts[QChar::Script_Tifinagh] = QStringLiteral("tifinagh");
        aseman_font_handler_scipts[QChar::Script_SylotiNagri] = QStringLiteral("sylotiNagri");
        aseman_font_handler_scipts[QChar::Script_OldPersian] = QStringLiteral("oldPersian");
        aseman_font_handler_scipts[QChar::Script_Kharoshthi] = QStringLiteral("kharoshthi");
        aseman_font_handler_scipts[QChar::Script_Balinese] = QStringLiteral("balinese");
        aseman_font_handler_scipts[QChar::Script_Cuneiform] = QStringLiteral("cuneiform");
        aseman_font_handler_scipts[QChar::Script_Phoenician] = QStringLiteral("phoenician");
        aseman_font_handler_scipts[QChar::Script_PhagsPa] = QStringLiteral("phagsPa");
        aseman_font_handler_scipts[QChar::Script_Nko] = QStringLiteral("nko");
        aseman_font_handler_scipts[QChar::Script_Sundanese] = QStringLiteral("sundanese");
        aseman_font_handler_scipts[QChar::Script_Lepcha] = QStringLiteral("lepcha");
        aseman_font_handler_scipts[QChar::Script_OlChiki] = QStringLiteral("olChiki");
        aseman_font_handler_scipts[QChar::Script_Vai] = QStringLiteral("vai");
        aseman_font_handler_scipts[QChar::Script_Saurashtra] = QStringLiteral("saurashtra");
        aseman_font_handler_scipts[QChar::Script_KayahLi] = QStringLiteral("kayahLi");
        aseman_font_handler_scipts[QChar::Script_Rejang] = QStringLiteral("rejang");
        aseman_font_handler_scipts[QChar::Script_Lycian] = QStringLiteral("lycian");
        aseman_font_handler_scipts[QChar::Script_Carian] = QStringLiteral("carian");
        aseman_font_handler_scipts[QChar::Script_Lydian] = QStringLiteral("lydian");
        aseman_font_handler_scipts[QChar::Script_Cham] = QStringLiteral("cham");
        aseman_font_handler_scipts[QChar::Script_TaiTham] = QStringLiteral("taiTham");
        aseman_font_handler_scipts[QChar::Script_TaiViet] = QStringLiteral("taiViet");
        aseman_font_handler_scipts[QChar::Script_Avestan] = QStringLiteral("avestan");
        aseman_font_handler_scipts[QChar::Script_EgyptianHieroglyphs] = QStringLiteral("egyptianHieroglyphs");
        aseman_font_handler_scipts[QChar::Script_Samaritan] = QStringLiteral("samaritan");
        aseman_font_handler_scipts[QChar::Script_Lisu] = QStringLiteral("lisu");
        aseman_font_handler_scipts[QChar::Script_Bamum] = QStringLiteral("bamum");
        aseman_font_handler_scipts[QChar::Script_Javanese] = QStringLiteral("javanese");
        aseman_font_handler_scipts[QChar::Script_MeeteiMayek] = QStringLiteral("meeteiMayek");
        aseman_font_handler_scipts[QChar::Script_ImperialAramaic] = QStringLiteral("imperialAramaic");
        aseman_font_handler_scipts[QChar::Script_OldSouthArabian] = QStringLiteral("oldSouthArabian");
        aseman_font_handler_scipts[QChar::Script_InscriptionalParthian] = QStringLiteral("inscriptionalParthian");
        aseman_font_handler_scipts[QChar::Script_InscriptionalPahlavi] = QStringLiteral("inscriptionalPahlavi");
        aseman_font_handler_scipts[QChar::Script_OldTurkic] = QStringLiteral("oldTurkic");
        aseman_font_handler_scipts[QChar::Script_Kaithi] = QStringLiteral("kaithi");
        aseman_font_handler_scipts[QChar::Script_Batak] = QStringLiteral("batak");
        aseman_font_handler_scipts[QChar::Script_Brahmi] = QStringLiteral("brahmi");
        aseman_font_handler_scipts[QChar::Script_Mandaic] = QStringLiteral("mandaic");
        aseman_font_handler_scipts[QChar::Script_Chakma] = QStringLiteral("chakma");
        aseman_font_handler_scipts[QChar::Script_MeroiticCursive] = QStringLiteral("meroiticCursive");
        aseman_font_handler_scipts[QChar::Script_MeroiticHieroglyphs] = QStringLiteral("meroiticHieroglyphs");
        aseman_font_handler_scipts[QChar::Script_Miao] = QStringLiteral("miao");
        aseman_font_handler_scipts[QChar::Script_Sharada] = QStringLiteral("sharada");
        aseman_font_handler_scipts[QChar::Script_SoraSompeng] = QStringLiteral("soraSompeng");
        aseman_font_handler_scipts[QChar::Script_Takri] = QStringLiteral("takri");
    }

    init();
}

QVariantMap AsemanFontHandler::fonts()
{
    return p->fonts;
}

void AsemanFontHandler::setFonts(const QVariantMap &fonts)
{
    if(p->fonts == fonts)
        return;

    p->fonts = fonts;
    Q_EMIT fontsChanged();
}

QFont AsemanFontHandler::fontOf(int script)
{
    const QString &key = aseman_font_handler_scipts.value(static_cast<QChar::Script>(script));
    return p->fonts.value(key).value<QFont>();
}

QString AsemanFontHandler::textToHtml(const QString &text)
{
    QString result;
    QChar::Script lastScript = QChar::Script_Unknown;

    int level = 0;
    for(int i=0; i<text.length(); i++)
    {
        const QChar &ch = text.at(i);
        if(ch == '<')
            level++;
        if(level > 0)
        {
            if(ch == '>')
                level--;

            result += ch;
            continue;
        }

        QChar::Script script = (ch=='&'? QChar::Script_Latin : ch.script());
        if(script <= QChar::Script_Common && lastScript != QChar::Script_Unknown)
            script = lastScript;

        if(lastScript != script)
        {
            if(lastScript != QChar::Script_Unknown)
                result += QStringLiteral("</span>");

            QString scriptKey = aseman_font_handler_scipts.value(script);
            QFont font = p->fonts.value(scriptKey).value<QFont>();

            result += QStringLiteral("<span style=\"font-family:'%1'; font-size:%2pt; font-style:%3;\">")
                    .arg(font.family()).arg(font.pointSize()).arg(font.styleName());
        }

        result += ch;
        lastScript = script;
    }

    return result;
}

QByteArray AsemanFontHandler::save()
{
    AsemanListRecord list;
    QMapIterator<QString, QVariant> i(p->fonts);
    while(i.hasNext())
    {
        i.next();
        AsemanListRecord record;
        record << i.key().toUtf8();
        record << i.value().toString().toUtf8();

        list << record.toQByteArray();
    }

    return list.toQByteArray();
}

void AsemanFontHandler::load(const QByteArray &data)
{
    AsemanListRecord list(data);
    for(int i=0; i<list.count(); i++)
    {
        AsemanListRecord record(list.at(i));
        if(record.count() != 2)
            continue;

        QFont font;
        font.fromString(QString::fromUtf8(record.last()));
        p->fonts[QString::fromUtf8(record.first())] = font;
    }

    Q_EMIT fontsChanged();
}

#ifdef QT_WIDGETS_LIB
void AsemanFontHandler::openFontChooser()
{
    QDialog dialog;
    dialog.resize(QSize(500, 400));

    QComboBox *comboBox = new QComboBox();
    comboBox->addItems(p->fonts.keys());

    QFontDialog *fontDlg = new QFontDialog();
    fontDlg->setWindowFlags(Qt::Widget);
    fontDlg->setWindowTitle(tr("Select font"));
    fontDlg->setOption(QFontDialog::DontUseNativeDialog);

    p->combo_hash[comboBox] = fontDlg;
    p->combo_cache[comboBox] = p->fonts;

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(comboBox);
    layout->addWidget(fontDlg);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(1);

    connect(comboBox, static_cast<void (QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged), this, &AsemanFontHandler::currentIndexChanged);
    connect(fontDlg , &QFontDialog::currentFontChanged, this, &AsemanFontHandler::currentFontChanged);

    connect(fontDlg, &QFontDialog::accepted, &dialog, &QDialog::accept);
    connect(fontDlg, &QFontDialog::rejected, &dialog, &QDialog::reject);

    comboBox->setCurrentText(QStringLiteral("latin"));
    comboBox->currentIndexChanged(QStringLiteral("latin"));

    if(dialog.exec() == QDialog::Accepted)
        p->fonts = p->combo_cache[comboBox];

    p->combo_hash.remove(comboBox);
    p->combo_cache.remove(comboBox);

    Q_EMIT fontsChanged();
}

void AsemanFontHandler::currentIndexChanged(const QString &key)
{
    QComboBox *comboBox = static_cast<QComboBox*>(sender());
    QFontDialog *fontDlg = p->combo_hash.value(comboBox);
    QFont font = p->combo_cache[comboBox][key].value<QFont>();
    fontDlg->setCurrentFont(font);
}

void AsemanFontHandler::currentFontChanged(const QFont &font)
{
    QFontDialog *fontDlg = static_cast<QFontDialog*>(sender());
    QComboBox *comboBox = p->combo_hash.key(fontDlg);
    QString key = comboBox->currentText();
    p->combo_cache[comboBox][key] = font;
}
#endif

void AsemanFontHandler::init()
{
    p->fonts.clear();
    QFont defaultFont;
    QMapIterator<int, QString> i(aseman_font_handler_scipts);
    while(i.hasNext())
    {
        i.next();
        p->fonts[i.value()] = defaultFont;
    }
}

AsemanFontHandler::~AsemanFontHandler()
{
    delete p;
}
