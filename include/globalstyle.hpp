#pragma once

#include <cstdint>
#include <QString>

/*
    I made this class because I had planned to have styles for every
    custom widget, this way every class would be able to access this
    sophisticated enum to read and interpret values stored in QSettings
    but I don't wanna emit a styleChanged from MainWindow and make it
    so that every single widget with custom style react to this,
    so I just made a global style in MainWindow making this class overkill
    but whatever
*/
class GlobalStyle {

public:
    enum Value : uint8_t {
        DEFAULT,
        AWESOME,
    };

    GlobalStyle() = default;
    constexpr GlobalStyle(Value style) : m_value(style) { }

    constexpr operator Value() const { return m_value; }

    explicit operator bool() const = delete;        

    inline QString toString() const;
    static inline GlobalStyle fromString(QString string);

private:
    Value m_value;

};

QString GlobalStyle::toString() const {
    switch (m_value) {
        case GlobalStyle::AWESOME: return "awesome";
        case GlobalStyle::DEFAULT: return "default";
        default: return "unknown"; // this shouldn't happen but just in case it does
    }
}

GlobalStyle GlobalStyle::fromString(QString string) {
    if (string == "awesome") return GlobalStyle::AWESOME;
    return GlobalStyle::DEFAULT;
}
