
#include <string.h>

#include "doomkeys.h"

#include "txt_checkbox.h"
#include "txt_io.h"
#include "txt_main.h"
#include "txt_window.h"

static void TXT_CheckBoxSizeCalc(UNCAST(checkbox), int *w, int *h)
{
    CAST(txt_checkbox_t, checkbox);

    // Minimum width is the string length + two spaces for padding

    *w = strlen(checkbox->label) + 6;
    *h = 1;
}

static void TXT_CheckBoxDrawer(UNCAST(checkbox), int w, int selected)
{
    CAST(txt_checkbox_t, checkbox);
    int i;

    TXT_BGColor(TXT_COLOR_BLUE, 0);
    TXT_FGColor(TXT_COLOR_BRIGHT_CYAN);
    TXT_DrawString(" (");

    TXT_FGColor(TXT_COLOR_BRIGHT_WHITE);

    if (*checkbox->variable)
    {
        TXT_DrawString("\x07");
    }
    else
    {
        TXT_DrawString(" ");
    }

    TXT_FGColor(TXT_COLOR_BRIGHT_CYAN);

    TXT_DrawString(") ");

    if (selected)
    {
        TXT_BGColor(TXT_COLOR_GREY, 0);
    }

    TXT_FGColor(TXT_COLOR_BRIGHT_WHITE);

    TXT_DrawString(checkbox->label);
    
    for (i=strlen(checkbox->label); i < w-6; ++i)
    {
        TXT_DrawString(" ");
    }
}

static void TXT_CheckBoxDestructor(UNCAST(checkbox))
{
    CAST(txt_checkbox_t, checkbox);

    free(checkbox->label);
}

static int TXT_CheckBoxKeyPress(UNCAST(checkbox), int key)
{
    CAST(txt_checkbox_t, checkbox);

    if (key == KEY_ENTER || key == ' ')
    {
        *checkbox->variable = !*checkbox->variable;
        TXT_EmitSignal(checkbox, "changed");
        return 1;
    }
    
    return 0;
}

txt_widget_class_t txt_checkbox_class =
{
    TXT_CheckBoxSizeCalc,
    TXT_CheckBoxDrawer,
    TXT_CheckBoxKeyPress,
    TXT_CheckBoxDestructor,
};

txt_checkbox_t *TXT_NewCheckBox(char *label, int *variable)
{
    txt_checkbox_t *checkbox;

    checkbox = malloc(sizeof(txt_checkbox_t));

    TXT_InitWidget(checkbox, &txt_checkbox_class);
    checkbox->label = strdup(label);
    checkbox->variable = variable;

    return checkbox;
}
