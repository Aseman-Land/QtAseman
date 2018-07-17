.pragma library

function insertAt(array, idx, item) {
    var result = new Array
    if(!array && idx == 0) {
        result[result.length] = item
        return result
    }

    var shoudAddAtEnd = (array.length == idx)
    for(var i=0; i<array.length; i++) {
        if(idx == i)
            result[result.length] = item

        result[result.length] = array[i]
    }
    if(shoudAddAtEnd)
        result[result.length] = item

    return result
}

function insertAfter(array, after, item) {
    var result = new Array
    if(!array)
        return result

    for(var i=0; i<array.length; i++) {
        var ch = array[i]
        result[result.length] = ch
        if(after == ch)
            result[result.length] = item
    }

    return result
}

function insertBefore(array, after, item) {
    var result = new Array
    if(!array)
        return result

    for(var i=0; i<array.length; i++) {
        var ch = array[i]
        if(after == ch)
            result[result.length] = item

        result[result.length] = ch
    }

    return result
}

function containt(array, item) {
    return array && array.indexOf(item) != -1
}

function removeAt(array, idx) {
    var result = new Array
    if(!array)
        return result

    for(var i=0; i<array.length; i++) {
        if(idx == i)
            continue

        result[result.length] = array[i]
    }

    return result
}

function remove(array, item) {
    var result = new Array
    if(!array)
        return result

    for(var i=0; i<array.length; i++) {
        var ch = array[i]
        if(ch == item)
            continue

        result[result.length] = ch
    }

    return result
}

function append(array, item) {
    return insertAt(array, array?array.length:0, item)
}

function prepend(array, item) {
    return insertAt(array, 0, item)
}

function move(array, from, to) {
    if(!array)
        return new Array
    if(from == to)
        return array

    var item = array[from]
    var dst = (from<to?to-1:to)
    var result = removeAt(array, from)
    result = insertAt(result, dst, item)

    return result
}

