#ifndef CORE_INPUT_INPUTTYPE_H
#define CORE_INPUT_INPUTTYPE_H


namespace MouseButtons
{
	enum Type
	{
		Left = 0,
		Middle,
		Right,
		Thumb01,
		Thumb02,

		Invalid,
	};
}


namespace ControllerButtons
{
	enum Type
	{
		LeftAnalogY = 0,
		LeftAnalogX,
		
		RightAnalogY,
		RightAnalogX,

		LeftTriggerAnalog,
		RightTriggerAnalog,

		FaceButtonBottom,
		FaceButtonRight,
		FaceButtonLeft,
		FaceButtonTop,
		LeftShoulder,
		RightShoulder,
		SpecialLeft,
		SpecialRight,
		LeftThumb,
		RightThumb,
		LeftTriggerThreshold,
		RightTriggerThreshold,
		DPadUp,
		DPadDown,
		DPadLeft,
		DPadRight,

		LeftStickUp,
		LeftStickDown,
		LeftStickLeft,
		LeftStickRight,

		RightStickUp,
		RightStickDown,
		RightStickLeft,
		RightStickRight,

		// Steam Controller
		Touch0,
		Touch1,
		Touch2,
		Touch3,
		BackLeft,
		BackRight,

		// global speech commands
		GlobalMenu,
		GlobalView,
		GlobalPause,
		GlobalPlay,
		GlobalBack,

		AndroidBack,
		AndroidVolumeUp,
		AndroidVolumeDown,
		AndroidMenu,

		Invalid,
	};
}


namespace WindowActivation
{
	enum Type
	{
		Activate = 0,
		ActivateByMouse,
		Deactivate
	};
}


namespace WindowZone
{
	/**
	 * The Window Zone is the window area we are currently over to send back to the operating system
	 * for operating system compliance.
	 */
	enum Type
	{
		NotInWindow			= 0,
		TopLeftBorder		= 1,
		TopBorder			= 2,
		TopRightBorder		= 3,
		LeftBorder			= 4,
		ClientArea			= 5,
		RightBorder			= 6,
		BottomLeftBorder	= 7,
		BottomBorder		= 8,
		BottomRightBorder	= 9,
		TitleBar			= 10,
		MinimizeButton		= 11,
		MaximizeButton		= 12,
		CloseButton			= 13,
		SysMenu				= 14,

		/** No zone specified */
		Unspecified	= 0,
	};
}


namespace WindowAction
{
	enum Type
	{
		ClickedNonClientArea	= 1,
		Maximize				= 2,
		Restore					= 3,
		WindowMenu				= 4,
	};
}


namespace DropEffect
{
	enum Type
	{
		None   = 0,
		Copy   = 1,
		Move   = 2,
		Link   = 3,
	};
}


namespace GestureEvent
{
	enum Type
	{
		None,
		Scroll,
		Magnify,
		Swipe,
		Rotate,
		Count
	};
}

#endif
