#pragma once

namespace utils::input {
    enum type {
        KEY,
        BUTTON,
    };

    void list_devices();
    bool is_down(int state_id, int device_id, type type);
    void send(int state_id, type type, bool down);
}
