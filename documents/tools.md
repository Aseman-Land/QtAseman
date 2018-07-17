# Tools

 * [Component details](#component-details)
 * [Methods](#methods)


### Component details:

|Detail|Value|
|------|-----|
|Import|AsemanTools 1.0|
|Component|<font color='#074885'>Tools</font>|
|C++ class|<font color='#074885'>AsemanTools</font>|
|Inherits|<font color='#074885'>object</font>|
|Model|<font color='#074885'>No</font>|



### Methods

 * void <font color='#074885'><b>debug</b></font>(variant var)
 * void <font color='#074885'><b>exportDocuments</b></font>(string destination)
 * QDateTime <font color='#074885'><b>currentDate</b></font>()
 * string <font color='#074885'><b>dateToMSec</b></font>(QDateTime dt)
 * QDateTime <font color='#074885'><b>mSecToDate</b></font>(string ms)
 * qlonglong <font color='#074885'><b>dateToSec</b></font>(QDateTime dt)
 * string <font color='#074885'><b>dateToString</b></font>(QDateTime dt, string format)
 * string <font color='#074885'><b>dateToString</b></font>(QDateTime dt)
 * string <font color='#074885'><b>fileName</b></font>(string path)
 * string <font color='#074885'><b>fileSuffix</b></font>(string path)
 * string <font color='#074885'><b>fileMime</b></font>(string path)
 * string <font color='#074885'><b>fileParent</b></font>(string path)
 * string <font color='#074885'><b>readText</b></font>(string path)
 * list&lt;string&gt; <font color='#074885'><b>filesOf</b></font>(string path)
 * boolean <font color='#074885'><b>writeFile</b></font>(string path, byte data)
 * byte <font color='#074885'><b>readFile</b></font>(string path)
 * string <font color='#074885'><b>className</b></font>(object obj)
 * list&lt;string&gt; <font color='#074885'><b>stringLinks</b></font>(string str)
 * url <font color='#074885'><b>stringToUrl</b></font>(string path)
 * string <font color='#074885'><b>urlToLocalPath</b></font>(url url)
 * string <font color='#074885'><b>qtVersion</b></font>()
 * string <font color='#074885'><b>aboutAseman</b></font>()
 * void <font color='#074885'><b>deleteItemDelay</b></font>(object o, int ms)
 * real <font color='#074885'><b>colorHue</b></font>(QColor clr)
 * real <font color='#074885'><b>colorLightness</b></font>(QColor clr)
 * real <font color='#074885'><b>colorSaturation</b></font>(QColor clr)
 * void <font color='#074885'><b>mkDir</b></font>(string dir)
 * map <font color='#074885'><b>colorHsl</b></font>(QColor clr)
 * boolean <font color='#074885'><b>createVideoThumbnail</b></font>(string video, string output, string ffmpegPath)
 * boolean <font color='#074885'><b>createVideoThumbnail</b></font>(string video, string output)
 * string <font color='#074885'><b>translateNumbers</b></font>(string input)
 * string <font color='#074885'><b>passToMd5</b></font>(string pass)
 * string <font color='#074885'><b>md5</b></font>(string str)
 * string <font color='#074885'><b>createUuid</b></font>()
 * string <font color='#074885'><b>htmlToPlaintText</b></font>(string html)
 * void <font color='#074885'><b>copyDirectory</b></font>(string src, string dst)
 * boolean <font color='#074885'><b>copy</b></font>(string src, string dst)
 * void <font color='#074885'><b>deleteFile</b></font>(string file)
 * void <font color='#074885'><b>clearDirectory</b></font>(string dir)
 * void <font color='#074885'><b>setProperty</b></font>(object obj, string property, variant v)
 * variant <font color='#074885'><b>property</b></font>(object obj, string property)
 * Qt::LayoutDirection <font color='#074885'><b>directionOf</b></font>(string str)
 * variant <font color='#074885'><b>call</b></font>(object obj, string member, Qt::ConnectionType type, variant v0, variant v1, variant v2, variant v3, variant v4, variant v5, variant v6, variant v7, variant v8, variant v9)
 * variant <font color='#074885'><b>call</b></font>(object obj, string member, Qt::ConnectionType type, variant v0, variant v1, variant v2, variant v3, variant v4, variant v5, variant v6, variant v7, variant v8)
 * variant <font color='#074885'><b>call</b></font>(object obj, string member, Qt::ConnectionType type, variant v0, variant v1, variant v2, variant v3, variant v4, variant v5, variant v6, variant v7)
 * variant <font color='#074885'><b>call</b></font>(object obj, string member, Qt::ConnectionType type, variant v0, variant v1, variant v2, variant v3, variant v4, variant v5, variant v6)
 * variant <font color='#074885'><b>call</b></font>(object obj, string member, Qt::ConnectionType type, variant v0, variant v1, variant v2, variant v3, variant v4, variant v5)
 * variant <font color='#074885'><b>call</b></font>(object obj, string member, Qt::ConnectionType type, variant v0, variant v1, variant v2, variant v3, variant v4)
 * variant <font color='#074885'><b>call</b></font>(object obj, string member, Qt::ConnectionType type, variant v0, variant v1, variant v2, variant v3)
 * variant <font color='#074885'><b>call</b></font>(object obj, string member, Qt::ConnectionType type, variant v0, variant v1, variant v2)
 * variant <font color='#074885'><b>call</b></font>(object obj, string member, Qt::ConnectionType type, variant v0, variant v1)
 * variant <font color='#074885'><b>call</b></font>(object obj, string member, Qt::ConnectionType type, variant v0)
 * variant <font color='#074885'><b>call</b></font>(object obj, string member, Qt::ConnectionType type)
 * void <font color='#074885'><b>jsDelayCall</b></font>(int ms, function(){[code]} value)



