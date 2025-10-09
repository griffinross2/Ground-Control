#pragma once

class AppLayer {
	
public:
	AppLayer() = default;
	~AppLayer() = default;
	
	virtual void Update() {}
    virtual void Render() {}

};