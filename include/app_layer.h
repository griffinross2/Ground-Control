#pragma once

class AppLayer {
public:
    AppLayer() = default;
    ~AppLayer() = default;

    virtual void Update() {}
    virtual void Render() {}
    void SetVisible(bool visible) { m_visible = visible; }

protected:
    bool m_visible = true;
};