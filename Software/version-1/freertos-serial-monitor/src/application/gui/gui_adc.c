/**
 *******************************************************************************
 * @file  gui_adc.c
 * @author  Hampus Sandberg
 * @version 0.1
 * @date  2015-08-15
 * @brief
 *******************************************************************************
  Copyright (c) 2015 Hampus Sandberg.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "gui_adc.h"

#include "max1301.h"

/* Private defines -----------------------------------------------------------*/
/* Private typedefs ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static GUITextBox prvTextBox = {0};
static GUIButton prvButton = {0};
static GUIContainer prvContainer = {0};

/* Private function prototypes -----------------------------------------------*/
/* Functions -----------------------------------------------------------------*/
/* ADC GUI Elements ========================================================*/
/**
 * @brief	Manages how data is displayed in the main text box when the source is ADC
 * @param	None
 * @retval	None
 */
void guiAdcManageMainTextBox(bool ShouldRefresh)
{
	/* Update the text box for channel 0 */
	GUITextBox_ClearAndResetWritePosition(GUITextBoxId_Adc0Value);
	GUITextBox_SetYWritePositionToCenter(GUITextBoxId_Adc0Value);
	int16_t currentValue = MAX1301_GetDataFromDiffChannel(MAX1301DiffChannel_0);
	GUITextBox_WriteNumber(GUITextBoxId_Adc0Value, (int32_t)currentValue);
	GUITextBox_WriteString(GUITextBoxId_Adc0Value, " V");

//	/* Update the text box for channel 1 */
//	GUITextBox_ClearAndResetWritePosition(GUITextBoxId_Adc1Value);
//	GUITextBox_SetYWritePositionToCenter(GUITextBoxId_Adc1Value);
//	currentValue = MAX1301_GetDataFromDiffChannel(MAX1301DiffChannel_1);
//	GUITextBox_WriteNumber(GUITextBoxId_Adc1Value, (int32_t)currentValue);
//	GUITextBox_WriteString(GUITextBoxId_Adc1Value, " V");
}

/**
 * @brief
 * @param	Event: The event that caused the callback
 * @param	ButtonId: The button ID that the event happened on
 * @retval	None
 */
void guiAdcTopButtonCallback(GUITouchEvent Event, uint32_t ButtonId)
{
	if (Event == GUITouchEvent_Up)
	{
		GUIDisplayState displayState = GUIContainer_GetDisplayState(GUIContainerId_SidebarAdc);
		lcdChangeDisplayStateOfSidebar(GUIContainerId_SidebarAdc);
	}
}

/**
 * @brief
 * @param	None
 * @retval	None
 */
void guiAdcInitGuiElements()
{
	/* Text boxes ----------------------------------------------------------------*/
	/* ADC Label text box */
	prvTextBox.object.id = GUITextBoxId_AdcLabel;
	prvTextBox.object.xPos = 650;
	prvTextBox.object.yPos = 50;
	prvTextBox.object.width = 150;
	prvTextBox.object.height = 50;
	prvTextBox.object.border = GUIBorder_Top | GUIBorder_Bottom | GUIBorder_Left;
	prvTextBox.object.borderThickness = 1;
	prvTextBox.object.borderColor = GUI_WHITE;
	prvTextBox.object.containerPage = GUIContainerPage_All;
	prvTextBox.textColor = GUI_MAGENTA;
	prvTextBox.backgroundColor = GUI_WHITE;
	prvTextBox.staticText = "ADC";
	prvTextBox.textSize = LCDFontEnlarge_2x;
	GUITextBox_Add(&prvTextBox);

	/* ADC channel 0 Value text box */
	prvTextBox.object.id = GUITextBoxId_Adc0Value;
	prvTextBox.object.xPos = 50;
	prvTextBox.object.yPos = 200;
	prvTextBox.object.width = 300;
	prvTextBox.object.height = 50;
	prvTextBox.object.containerPage = GUIContainerPage_1;
	prvTextBox.textColor = GUI_MAGENTA;
	prvTextBox.backgroundColor = GUI_WHITE;
	prvTextBox.textSize = LCDFontEnlarge_2x;
	GUITextBox_Add(&prvTextBox);

	/* ADC channel 1 Value text box */
	prvTextBox.object.id = GUITextBoxId_Adc1Value;
	prvTextBox.object.xPos = 50;
	prvTextBox.object.yPos = 300;
	prvTextBox.object.width = 300;
	prvTextBox.object.height = 50;
	prvTextBox.object.containerPage = GUIContainerPage_1;
	prvTextBox.textColor = GUI_MAGENTA;
	prvTextBox.backgroundColor = GUI_WHITE;
	prvTextBox.textSize = LCDFontEnlarge_2x;
	GUITextBox_Add(&prvTextBox);

	/* Buttons -------------------------------------------------------------------*/
	/* ADC Top Button */
	prvButton.object.id = GUIButtonId_AdcTop;
	prvButton.object.xPos = 600;
	prvButton.object.yPos = 0;
	prvButton.object.width = 50;
	prvButton.object.height = 50;
	prvButton.object.displayState = GUIDisplayState_NotHidden;
	prvButton.object.border = GUIBorder_Bottom | GUIBorder_Right | GUIBorder_Left;
	prvButton.object.borderThickness = 1;
	prvButton.object.borderColor = GUI_WHITE;
	prvButton.enabledTextColor = GUI_WHITE;
	prvButton.enabledBackgroundColor = GUI_MAGENTA;
	prvButton.disabledTextColor = GUI_MAGENTA;
	prvButton.disabledBackgroundColor = LCD_COLOR_BLACK;
	prvButton.pressedTextColor = GUI_MAGENTA;
	prvButton.pressedBackgroundColor = GUI_WHITE;
	prvButton.state = GUIButtonState_DisabledTouch;			/* TODO: Something is wrong with ADC, so disabled for now */
	prvButton.touchCallback = guiAdcTopButtonCallback;
	prvButton.text[0] = "ADC";
	prvButton.textSize[0] = LCDFontEnlarge_1x;
	GUIButton_Add(&prvButton);

	/* ADC Enable Button */
	prvButton.object.id = GUIButtonId_AdcEnable;
	prvButton.object.xPos = 650;
	prvButton.object.yPos = 100;
	prvButton.object.width = 150;
	prvButton.object.height = 50;
	prvButton.object.border = GUIBorder_Top | GUIBorder_Bottom | GUIBorder_Left;
	prvButton.object.borderThickness = 1;
	prvButton.object.borderColor = GUI_WHITE;
	prvButton.object.containerPage = GUIContainerPage_1;
	prvButton.enabledTextColor = GUI_WHITE;
	prvButton.enabledBackgroundColor = GUI_MAGENTA;
	prvButton.disabledTextColor = GUI_WHITE;
	prvButton.disabledBackgroundColor = GUI_MAGENTA;
	prvButton.pressedTextColor = GUI_MAGENTA;
	prvButton.pressedBackgroundColor = GUI_WHITE;
	prvButton.state = GUIButtonState_Disabled;
	prvButton.touchCallback = 0;
	prvButton.text[0] = "Output:";
//	prvButton.text[1] = "Enabled";
	prvButton.text[1] = "Disabled";
	prvButton.textSize[0] = LCDFontEnlarge_1x;
	prvButton.textSize[1] = LCDFontEnlarge_1x;
	GUIButton_Add(&prvButton);

	/* Containers ----------------------------------------------------------------*/
	/* Sidebar ADC container */
	prvContainer.object.id = GUIContainerId_SidebarAdc;
	prvContainer.object.xPos = 650;
	prvContainer.object.yPos = 50;
	prvContainer.object.width = 150;
	prvContainer.object.height = 400;
	prvContainer.object.border = GUIBorder_Left | GUIBorder_Top | GUIBorder_Bottom;
	prvContainer.object.borderThickness = 1;
	prvContainer.object.borderColor = GUI_WHITE;
	prvContainer.activePage = GUIContainerPage_1;
	prvContainer.contentHideState = GUIHideState_KeepBorders;
	prvContainer.buttons[0] = GUIButton_GetFromId(GUIButtonId_AdcEnable);
	prvContainer.textBoxes[0] = GUITextBox_GetFromId(GUITextBoxId_AdcLabel);
	GUIContainer_Add(&prvContainer);

	/* ADC main container */
	prvContainer.object.id = GUIContainerId_AdcMainContent;
	prvContainer.object.xPos = 0;
	prvContainer.object.yPos = 50;
	prvContainer.object.width = 650;
	prvContainer.object.height = 400;
	prvContainer.object.containerPage = guiConfigMAIN_CONTAINER_ADC_PAGE;
	prvContainer.object.border = GUIBorder_Right | GUIBorder_Top;
	prvContainer.object.borderThickness = 2;
	prvContainer.object.borderColor = GUI_WHITE;
	prvContainer.activePage = GUIContainerPage_1;
	prvContainer.backgroundColor = GUI_BLACK;
	prvContainer.contentHideState = GUIHideState_HideAll;
	prvContainer.textBoxes[0] = GUITextBox_GetFromId(GUITextBoxId_Adc0Value);
	prvContainer.textBoxes[1] = GUITextBox_GetFromId(GUITextBoxId_Adc1Value);
	GUIContainer_Add(&prvContainer);
}

/* Interrupt Handlers --------------------------------------------------------*/
