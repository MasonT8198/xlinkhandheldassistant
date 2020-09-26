#pragma once

/* Copyright (c) 2020 [Rick de Bondt] - Window.h
 *
 * This file contains an class for a userinterface window.
 *
 **/

#include <functional>
#include <memory>
#include <string>

#include <ncurses.h>
#undef timeout

#include "IWindow.h"

/**
 * Class with basic functions to setup a window.
 */
class Window : public IWindow
{
public:
    Window(std::string_view aTitle,
           int              aYCoord,
           int              aXCoord,
           int              aLines,
           int              aColumns,
           bool             aExclusive = false,
           bool             aVisible   = true);

    Window(const Window& aWindow) = delete;
    Window& operator=(const Window& aWindow) = delete;

    Window& operator=(Window&& aWindow) = delete;
    Window(Window&& aWindow)            = default;

    ~Window() = default;

    void SetUp() override;

    void Draw() override;

    void DrawString(int aYCoord, int aXCoord, int aColorPair, std::string_view aString);

    void AddObject(std::unique_ptr<IUIObject> aObject) override;

    void Refresh() override;

    bool Move(int aYCoord, int aXCoord) override;

    std::pair<int, int> GetSize() override;

    bool Resize(int aLines, int aColumns) override;

    bool Scale(int aMaxHeight, int aMaxWidth) override;

    bool AdvanceSelectionVertical() override;

    bool RecedeSelectionVertical() override;

    bool AdvanceSelectionHorizontal() override;

    bool RecedeSelectionHorizontal() override;

    bool DoSelection() override;

    void SetExclusive(bool aExclusive) override;

    bool IsExclusive() override;

    void SetVisible(bool aVisible) override;

    bool IsVisible() override;

private:
    std::unique_ptr<WINDOW, std::function<void(WINDOW*)>> mNCursesWindow;
    std::string                                           mTitle;
    int                                                   mLines;
    int                                                   mColumns;
    bool                                                  mDimensionsChanged;
    bool                                                  mExclusive;
    bool                                                  mVisible;
    std::vector<std::unique_ptr<IUIObject>>               mObjects;
};
