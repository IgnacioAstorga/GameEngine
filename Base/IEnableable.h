#ifndef __IEnableable_H__
#define __IEnableable_H__

class IEnableable {

/// Constructors
public:
	IEnableable() {};
	virtual ~IEnableable() {};

/// Public methods
public:
	// Enables the object
	void Enable() { 
		SetEnabled(true);
	}

	// Disables the object
	void Disable() { 
		SetEnabled(false);
	}

	// Sets the enabled state of the object
	void SetEnabled(bool state) {
		// Checks if the enabled state will change and calls the right method
		if (enabled && !state)
			OnDisable();
		else if (!enabled && state)
			OnEnable();
		enabled = state;
	}

	// Returns if the object is enabled or not
	bool IsEnabled() const {
		return enabled;
	}

/// Delegated methods
protected:
	// Called when the object is enabled
	virtual void OnEnable() = 0;

	// Called when the object is disabled
	virtual void OnDisable() = 0;

/// Attributes
private:
	// If the object is enabled or not
	bool enabled = true;
};

#endif