#pragma once
#include <QString>
#include <QMetaType>

enum class MovementDirection {
    Up,
    Down,
    Left,
    Right,
    Forward,
    Backward
};

Q_DECLARE_METATYPE(MovementDirection)

inline QString toQString(MovementDirection direction) {
    switch (direction) {
    case MovementDirection::Up: return "UP";
    case MovementDirection::Down: return "DOWN";
    case MovementDirection::Left: return "LEFT";
    case MovementDirection::Right: return "RIGHT";
    case MovementDirection::Forward: return "FORWARD";
    case MovementDirection::Backward: return "BACKWARD";
    default: return "";
    }
}
