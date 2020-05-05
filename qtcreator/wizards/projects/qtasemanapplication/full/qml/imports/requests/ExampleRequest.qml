import QtQuick 2.0
import AsemanQml.Base 2.0
import globals 1.0

BaseRequest {
    id: todoRequest
    url: baseUrl + "/todos"

    onRefreshRequest: refresh()

    function refresh() {
        if (refreshing)
            return;

        _networkManager.get(todoRequest);
    }
}
