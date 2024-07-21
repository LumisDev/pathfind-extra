#include <node_api.h>
#include "a_star.h"

napi_value AStarPathfinding(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    if (argc < 3) {
        napi_throw_type_error(env, nullptr, "Expected three arguments");
        return nullptr;
    }

    bool is_array;
    napi_is_array(env, args[0], &is_array);
    if (!is_array) {
        napi_throw_type_error(env, nullptr, "Expected an array for grid");
        return nullptr;
    }

    napi_is_array(env, args[1], &is_array);
    if (!is_array) {
        napi_throw_type_error(env, nullptr, "Expected an array for start");
        return nullptr;
    }

    napi_is_array(env, args[2], &is_array);
    if (!is_array) {
        napi_throw_type_error(env, nullptr, "Expected an array for goal");
        return nullptr;
    }

    napi_value gridArray = args[0];
    napi_value startArray = args[1];
    napi_value goalArray = args[2];

    uint32_t gridLength;
    napi_get_array_length(env, gridArray, &gridLength);

    std::vector<std::vector<int>> grid;
    for (uint32_t i = 0; i < gridLength; ++i) {
        napi_value row;
        napi_get_element(env, gridArray, i, &row);

        uint32_t rowLength;
        napi_get_array_length(env, row, &rowLength);

        std::vector<int> gridRow;
        for (uint32_t j = 0; j < rowLength; ++j) {
            napi_value value;
            napi_get_element(env, row, j, &value);

            int32_t intValue;
            napi_get_value_int32(env, value, &intValue);
            gridRow.push_back(intValue);
        }
        grid.push_back(gridRow);
    }

    int32_t startX, startY, goalX, goalY;
    napi_value startXValue, startYValue, goalXValue, goalYValue;

    napi_get_element(env, startArray, 0, &startXValue);
    napi_get_element(env, startArray, 1, &startYValue);
    napi_get_element(env, goalArray, 0, &goalXValue);
    napi_get_element(env, goalArray, 1, &goalYValue);

    napi_get_value_int32(env, startXValue, &startX);
    napi_get_value_int32(env, startYValue, &startY);
    napi_get_value_int32(env, goalXValue, &goalX);
    napi_get_value_int32(env, goalYValue, &goalY);

    Node start(startX, startY);
    Node goal(goalX, goalY);

    std::vector<Node> path = astar(grid, start, goal);

    napi_value result;
    napi_create_array_with_length(env, path.size(), &result);

    for (size_t i = 0; i < path.size(); ++i) {
        napi_value point;
        napi_create_array_with_length(env, 2, &point);

        napi_value x, y;
        napi_create_int32(env, path[i].x, &x);
        napi_create_int32(env, path[i].y, &y);

        napi_set_element(env, point, 0, x);
        napi_set_element(env, point, 1, y);

        napi_set_element(env, result, i, point);
    }

    return result;
}

napi_value Init(napi_env env, napi_value exports) {
    napi_value fn;
    napi_create_function(env, nullptr, 0, AStarPathfinding, nullptr, &fn);
    napi_set_named_property(env, exports, "astar", fn);
    return exports;
}

NAPI_MODULE(pathfinding, Init)
