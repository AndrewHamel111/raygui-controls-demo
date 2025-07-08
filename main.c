#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "external/raygui.h"

#include "debug/debug.h"
#include "debug/debug_menu.h"

const int screenWidth = 1024;
const int screenHeight = 1024;

void QLAY_Reset(float X, float Y);
void QLAY_Config(float Width, float Height, float Padding);
Rectangle QLAY_Next();
Rectangle QLAY_NextSize(float width, float height);
Rectangle QLAY_Custom(float width, float height, float Xoff, float Yoff);
void QLAY_PushIndent();
void QLAY_PopIndent();

Vector2 scroll_vector;
Rectangle scroll_view;

bool toggle_state;
int toggle_group_active;
int dropdown_active;
bool dropdown_edit;
int spinner_value;
bool spinner_edit;
int value_value;
bool value_edit;
float value_valuef;
bool value_editf;
char float_value_raw[50];
char text_box_raw[50];
bool text_edit;
float slider_value;
Vector2 mouse_cell;

int list_view_scroll;
int list_view_active;
const char* list_views[] = {"Option 1", "Option 2", "Option 3?", "Option 4", "Option 5"};
int list_view_scroll2;
int list_view_active2;
int list_view_focus2;
bool gui_message_box;
bool gui_text_input_box;
char input_box_text[50];
int unused;

extern bool _WindowBox;
extern bool _MessageBox;
extern bool _TextInputBox;

Texture2D scroll_image;

int main(void)
{
    InitWindow(screenWidth, screenWidth, "Raygui Overview");
    SetTargetFPS(60);
    
    scroll_image = LoadTexture("scroll.png");
    
    Color background = WHITE;
    while (!WindowShouldClose())
    {
        QLAY_Reset(10, 10);
        
        BeginDrawing();
        {
            ClearBackground(background);
            
            if (DebugWindowBox())
                if (GuiWindowBox(QLAY_NextSize(400, 200), "Window Box"))
                    _WindowBox = false;
                
            if (DebugGroupBox())
                GuiGroupBox(QLAY_NextSize(400, 200), "Group Box");
            
            if (DebugLine())
                GuiLine(QLAY_NextSize(200, 10), "Line");
            
            if (DebugPanel())
                GuiPanel(QLAY_NextSize(400, 200), "Panel");
            
            if (DebugTabBar())
                GuiTabBar(QLAY_NextSize(200, 50), list_views, 5, &unused);
            
            if (DebugScrollPanel())
            {
                Rectangle scroll = QLAY_NextSize(400, 200);
                Rectangle scroll_content = scroll;
                scroll_content.width = 0;
                scroll_content.height *= 4;
                
                GuiScrollPanel(scroll, "Scroll Panel", scroll_content, &scroll_vector, &scroll_view);
                scroll.x += 1;
                scroll.y += 24;
                scroll.width -= 14;
                scroll.height -= 25;
                Rectangle scroll_source = { 0, -scroll_vector.y, scroll_image.width, scroll_view.height };
                DrawTexturePro(scroll_image, scroll_source, scroll, (Vector2){0}, 0, WHITE);
            }
            
            if (DebugLabel())
                GuiLabel(QLAY_NextSize(200, 10), "Label");
            
            if (DebugButton() && GuiButton(QLAY_Next(), "Change BG"))
                background = (Color){GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255)};
            
            if (DebugLabelButton() && GuiLabelButton(QLAY_NextSize(200, 10), "Label Button"))
                background = WHITE;
            
            if (DebugToggle())
                GuiToggle(QLAY_Next(), "Toggle", &toggle_state);
            
            if (DebugToggleGroup())
                GuiToggleGroup(QLAY_Custom(200, 20, 0, 74), "Toggle Group 1\nToggle Group 2\nToggle Group 3", &toggle_group_active);
            
            if (DebugToggleSlider())
                GuiToggleSlider(QLAY_NextSize(200, 20), "No. 1\nNo. 2\nNo. 3", &toggle_group_active);
            
            if (DebugCheckBox())
                GuiCheckBox(QLAY_NextSize(20, 20), "Check Box", &toggle_state);
            
            if (DebugComboBox())
                GuiComboBox(QLAY_NextSize(200, 20), "Toggle Group 1\nToggle Group 2\nToggle Group 3", &toggle_group_active);
            
            if (DebugDropdownBox() && GuiDropdownBox(QLAY_NextSize(200, 20), "Dropdown Box\nMany Options\nVery cool", &dropdown_active, dropdown_edit))
                dropdown_edit = !dropdown_edit;
            if (DebugDropdownBox() && dropdown_edit)
                QLAY_NextSize(0, 54);
            
            QLAY_PushIndent();
            QLAY_PushIndent();
            QLAY_PushIndent();
            {
                if (DebugSpinner() && GuiSpinner(QLAY_NextSize(200, 20), "Spinner", &spinner_value, 0, 10, spinner_edit))
                    spinner_edit = !spinner_edit;
                
                if (DebugValueBox() && GuiValueBox(QLAY_NextSize(200, 20), "Value Box", &value_value, 0, 10, value_edit))
                    value_edit = !value_edit;
                
                if (DebugValueBoxFloat() && GuiValueBoxFloat(QLAY_NextSize(200, 20), "Value Box", float_value_raw, &value_valuef, value_editf))
                    value_editf = !value_editf;
            }
            QLAY_PopIndent();
            QLAY_PopIndent();
            QLAY_PopIndent();
            
            if (DebugTextBox() && GuiTextBox(QLAY_NextSize(200, 80), text_box_raw, 60, text_edit))
                text_edit = !text_edit;
            
            QLAY_PushIndent();
            {
                if (DebugSlider())
                    GuiSlider(QLAY_NextSize(200, 10), "Left", "Right", &slider_value, 0, 100);
                if (DebugSliderBar())
                    GuiSliderBar(QLAY_NextSize(200, 10), "Left", "Right", &slider_value, 0, 100);
                if (DebugProgressBar())
                    GuiProgressBar(QLAY_NextSize(200, 40), "Left", "Right", &slider_value, 0, 100);
            }
            QLAY_PopIndent();
            
            if (DebugDummyRec())
                GuiDummyRec(QLAY_Next(), "Dummy");
            if (DebugGrid())
                GuiGrid(QLAY_NextSize(100, 100), "Grid", 50, 10, &mouse_cell);
            
            if (DebugStatusBar())
                GuiStatusBar((Rectangle){0, screenHeight - 20, screenWidth, 20}, TextFormat("Mouse in: [%d, %d]", (int)mouse_cell.x, (int)mouse_cell.y));
            
            if (DebugListView())
                GuiListView(QLAY_NextSize(200, 90), "List View\nMany Options\nSo cool\nPizza Hut\nDominos\nNew Orleans\nLittle Caesars\nPizza Pizza\nGreco's\nNorth of Brooklyn Pizzeria", &list_view_scroll, &list_view_active);
            if (DebugListViewEx())
                GuiListViewEx(QLAY_NextSize(200, 90), list_views, 5, &list_view_scroll2, &list_view_active2, &list_view_focus2);
            
            if (DebugColorPicker())
                GuiColorPicker(QLAY_NextSize(200, 200), "Color Picker", &background);
            
            if (DebugMessageBox())
            {
                DrawRectangle(0, 0, screenWidth, screenHeight, GetColor(0xffffffaa));
                if (GuiMessageBox((Rectangle){screenWidth / 2 - 250, screenHeight /2 - 100, 500, 200}, "Message Box", "This is a GuiMessageBox!", "Ok\nGreat\nCool") >= 0)
                {
                    _MessageBox = false;
                }
            }
            
            if (DebugTextInputBox())
            {
                DrawRectangle(0, 0, screenWidth, screenHeight, GetColor(0xffffffaa));
                bool bUnused;
                if (GuiTextInputBox((Rectangle){screenWidth / 2 - 250, screenHeight /2 - 100, 500, 200}, "Gui Text Input Box", "This is a GuiTextInputBox! Don't tell anyone ok?????", "Yes sir\nPerhaps", input_box_text, 20, &bUnused) >= 0)
                {
                    _TextInputBox = false;
                }
            }
            
            DebugMenuDraw();
        }
        EndDrawing();
    }
    
    CloseWindow();
}

float QLAY_X;
float QLAY_Y;

float QLAY_Root_X;
float QLAY_Root_Y;

float QLAY_Width = 200;
float QLAY_Height = 80;
float QLAY_Padding = 10;
int QLAY_Indent = 0;

int QLAY_Half = 0;

void QLAY_Reset(float X, float Y)
{
    QLAY_Root_X = QLAY_X = X;
    QLAY_Root_Y = QLAY_Y = Y;
}

void QLAY_Config(float Width, float Height, float Padding)
{
    QLAY_Width = Width;
    QLAY_Height = Height;
    QLAY_Padding = Padding;
}

Rectangle QLAY_Next()
{
    float X,Y;
    X = QLAY_X + (QLAY_Indent * QLAY_Padding * 3);
    Y = QLAY_Y;
    
    QLAY_Y += QLAY_Height + QLAY_Padding;
    
    return (Rectangle){ X, Y, QLAY_Width, QLAY_Height };
}

Rectangle QLAY_NextSize(float width, float height)
{
    float X,Y;
    X = QLAY_X + (QLAY_Indent * QLAY_Padding * 3);
    Y = QLAY_Y;
    
    QLAY_Y += height + QLAY_Padding;
    
    return (Rectangle){ X, Y, width, height };
}

Rectangle QLAY_Custom(float width, float height, float Xoff, float Yoff)
{
    float X,Y;
    X = QLAY_X + (QLAY_Indent * QLAY_Padding * 3);
    Y = QLAY_Y;
    
    QLAY_X += Xoff;
    QLAY_Y += Yoff;
    
    return (Rectangle){ X, Y, width, height };
}

void QLAY_PushIndent()
{
    QLAY_Indent++;
}

void QLAY_PopIndent()
{
    QLAY_Indent--;
    if (QLAY_Indent < 0)
        QLAY_Indent = 0;
}