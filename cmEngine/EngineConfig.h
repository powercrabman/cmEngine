#pragma once

namespace cmEngine
{

#define CONFIG_BODY(ConfigType, FileName, ...)                           \
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ConfigType, __VA_ARGS__);             \
    const wchar_t* GetConfigPath() const override { return FileName; }   \
    const char* ToString() const override { return #ConfigType; }

    struct ConfigBase
    {
        virtual const wchar_t* GetConfigPath() const abstract;
        virtual const char* ToString() const abstract;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(WindowResolution, Width, Height);
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(WindowPosition, X, Y);

    struct WindowConfig : public ConfigBase
    {
        WindowResolution Resolution = { 0, 0 };
        WindowPosition Position = { 0, 0 };

        CONFIG_BODY(WindowConfig, L"WindowConfig.json", Resolution, Position);
    };

    struct RendererConfig : public ConfigBase
    {
        Color ClearColor;

        CONFIG_BODY(RendererConfig, L"RendererConfig.json", ClearColor);
    };

    struct LogConfig : public ConfigBase
    {
        ImVec4 LogTraceTextColor;
        ImVec4 LogDebugTextColor;
        ImVec4 LogWarnTextColor;
        ImVec4 LogErrorTextColor;
        ImVec4 LogFatalTextColor;
        ImVec4 LogInfoTextColor;

        CONFIG_BODY(LogConfig, L"LogConfig.json",
            LogTraceTextColor,
            LogDebugTextColor,
            LogWarnTextColor,
            LogErrorTextColor,
            LogFatalTextColor,
            LogInfoTextColor
        );
    };
}
