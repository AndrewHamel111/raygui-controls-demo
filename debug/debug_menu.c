#include "debug_menu.h"
#include "debug.h"

#include "raylib.h"
#include "../external/raygui.h"

#define MENU_WIDTH 300

// --------------------------- //
// debug variables and getters //
// --------------------------- //

#define DEFINE_DEBUG_VAR(VAR_NAME) \
    bool _##VAR_NAME = false;\
    bool Debug##VAR_NAME() { return _##VAR_NAME; }
    
DEFINE_DEBUG_VAR(WindowBox);
DEFINE_DEBUG_VAR(GroupBox);
DEFINE_DEBUG_VAR(Line);
DEFINE_DEBUG_VAR(Panel);
DEFINE_DEBUG_VAR(TabBar);
DEFINE_DEBUG_VAR(ScrollPanel);

DEFINE_DEBUG_VAR(Label);
DEFINE_DEBUG_VAR(Button);
DEFINE_DEBUG_VAR(LabelButton);
DEFINE_DEBUG_VAR(Toggle);
DEFINE_DEBUG_VAR(ToggleGroup);
DEFINE_DEBUG_VAR(ToggleSlider);
DEFINE_DEBUG_VAR(CheckBox);
DEFINE_DEBUG_VAR(ComboBox);
DEFINE_DEBUG_VAR(DropdownBox);
DEFINE_DEBUG_VAR(Spinner);
DEFINE_DEBUG_VAR(ValueBox);
DEFINE_DEBUG_VAR(ValueBoxFloat);
DEFINE_DEBUG_VAR(TextBox);
DEFINE_DEBUG_VAR(Slider);
DEFINE_DEBUG_VAR(SliderBar);
DEFINE_DEBUG_VAR(ProgressBar);
DEFINE_DEBUG_VAR(DummyRec);
DEFINE_DEBUG_VAR(Grid);
DEFINE_DEBUG_VAR(StatusBar);

DEFINE_DEBUG_VAR(MessageBox);
DEFINE_DEBUG_VAR(TextInputBox);
DEFINE_DEBUG_VAR(ListView);
DEFINE_DEBUG_VAR(ListViewEx);
DEFINE_DEBUG_VAR(ColorPicker);

// ---------- //
// menu logic //
// ---------- //
static bool showDebugMenu;

static float X;
static float Y;

static float X_start;
static float Y_start;

static int Indent;

static Rectangle NextCheckboxRec()
{
    Rectangle r = {X + (Indent * 30), Y, 20, 20};

	Y += 20 + 10;

	return r;
}

static Rectangle NextLabel()
{
	Rectangle r = {X + (Indent * 30), Y, MENU_WIDTH, 10};

	Y += 10 + 10;

	return r;
}

static Rectangle NextSize(float width, float height)
{
    if (!width) width = MENU_WIDTH;
    
	Rectangle r = {X + (Indent * 30), Y, width, height};

	Y += 10 + height;

	return r;
}

static void PushIndent()
{
    Indent++;
}

static void PopIndent()
{
    Indent--;
    if (Indent < 0)
        Indent = 0;
}

#define LABEL_TOGGLE(TEXT, VAR) \
    static bool _##VAR; \
    if (GuiLabelButton(NextLabel(), TEXT)) \
        _##VAR = !_##VAR; \
    if (_##VAR)
#define BUTTON_TOGGLE(TEXT, VAR) \
    static bool _##VAR; \
    if (GuiButton(NextSize(150, 20), TEXT)) \
        _##VAR = !_##VAR; \
    if (_##VAR)
        
#define DEBUG_CHECKBOX(VAR) \
    GuiCheckBox(NextCheckboxRec(), #VAR, &_##VAR)

// --------------- //
// debug menu draw //
// --------------- //

void DebugMenuDraw()
{
	if (IsKeyPressed(KEY_GRAVE))
	{
		showDebugMenu = !showDebugMenu;
		Vector2 mpos = GetMousePosition();
		X_start = mpos.x;
		Y_start = mpos.y;
	}

	if (!showDebugMenu)
	{
		return;
	}

	X = X_start + 10;
	Y = Y_start + 10;
    
    BUTTON_TOGGLE("Basic Controls", _bc)
    {
        LABEL_TOGGLE("Separators", _sp)
        {
            PushIndent();
            DEBUG_CHECKBOX(WindowBox);
            DEBUG_CHECKBOX(GroupBox);
            DEBUG_CHECKBOX(Line);
            DEBUG_CHECKBOX(Panel);
            DEBUG_CHECKBOX(TabBar);
            DEBUG_CHECKBOX(ScrollPanel);
            PopIndent();
        }
        LABEL_TOGGLE("Buttons and Toggles", _bt)
        {
            PushIndent();
            DEBUG_CHECKBOX(Label);
            DEBUG_CHECKBOX(Button);
            DEBUG_CHECKBOX(LabelButton);
            DEBUG_CHECKBOX(Toggle);
            DEBUG_CHECKBOX(ToggleGroup);
            DEBUG_CHECKBOX(ToggleSlider);
            DEBUG_CHECKBOX(CheckBox);
            DEBUG_CHECKBOX(ComboBox);
            DEBUG_CHECKBOX(DropdownBox); 
            PopIndent();
        }
        LABEL_TOGGLE("Value Entry", _ve)
        {
            PushIndent();
            DEBUG_CHECKBOX(Spinner);
            DEBUG_CHECKBOX(ValueBox);
            DEBUG_CHECKBOX(ValueBoxFloat);
            DEBUG_CHECKBOX(TextBox);
            DEBUG_CHECKBOX(Slider);
            DEBUG_CHECKBOX(SliderBar);
            PopIndent();
        }
        LABEL_TOGGLE("Other", _orc)
        {
            PushIndent();
            DEBUG_CHECKBOX(ProgressBar);
            DEBUG_CHECKBOX(DummyRec);
            DEBUG_CHECKBOX(Grid);
            DEBUG_CHECKBOX(StatusBar);
            PopIndent();
        }
    }
    
    BUTTON_TOGGLE("Advanced Controls", _ac)
    {
        PushIndent();
        DEBUG_CHECKBOX(MessageBox);
        DEBUG_CHECKBOX(TextInputBox);
        DEBUG_CHECKBOX(ListView);
        DEBUG_CHECKBOX(ListViewEx);
        DEBUG_CHECKBOX(ColorPicker);
        PopIndent();
    }
}