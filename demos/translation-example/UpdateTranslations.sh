#! /bin/sh

# Set the home if not already set.
if [ "${MEIKADE_SRC_PATH}" = "" ]; then
    MEIKADE_SRC_PATH="`echo $0 | grep ^/`"
    if [ "$MEIKADE_SRC_PATH" = "" ]; then
    MEIKADE_SRC_PATH="$PWD"/"$0"
    fi
    cd `dirname $MEIKADE_SRC_PATH`
    MEIKADE_SRC_PATH=$PWD
    cd -
fi

cd $MEIKADE_SRC_PATH
for TRANSLATION in ./translations_sources/*.ts
do
    lupdate `find -name '*.cpp' -type f` \
            `find -name '*.qml' -type f` \
            `find -name '*.h' -type f` \
            `find -name '*.ui' -type f` \
            -ts "$TRANSLATION"
done

