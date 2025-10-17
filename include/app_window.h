#pragma once

class AppWindow {
public:
    AppWindow() = default;
    ~AppWindow() = default;

    virtual void Update() {}
    virtual void Render() {}
    void SetVisible(bool visible) { m_visible = visible; }

protected:
    bool m_visible = true;
};
