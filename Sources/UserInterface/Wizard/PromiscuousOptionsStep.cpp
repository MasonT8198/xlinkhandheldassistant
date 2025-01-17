/* Copyright (c) 2021 [Rick de Bondt] - PromiscuousOptionsStep.cpp */

#include "UserInterface/Wizard/PromiscuousOptionsStep.h"

#include "UserInterface/Button.h"
#include "UserInterface/CheckBox.h"
#include "UserInterface/DefaultElements.h"
#include "UserInterface/RadioBoxGroup.h"
#include "UserInterface/TextField.h"

namespace
{
    Window::Dimensions ScaleAutoConnectCheckBox() { return {2, 4, 0, 0}; }
    Window::Dimensions ScaleReConnectionTimeOutTextField() { return {3, 4, 0, 0}; }
    Window::Dimensions ScaleXLinkSSIDCheckBox() { return {4, 4, 0, 0}; }
    Window::Dimensions ScaleHostSSIDCheckBox() { return {4, 4, 0, 0}; }
    Window::Dimensions ScaleUseWifiAdapterRadioBoxGroup() { return {5, 4, 0, 0}; }

}  // namespace

PromiscuousOptionsStep::PromiscuousOptionsStep(WindowModel&                        aModel,
                                               std::string_view                    aTitle,
                                               std::function<Window::Dimensions()> aCalculation) :
    Window(aModel, aTitle, aCalculation)
{}

void PromiscuousOptionsStep::SetUp()
{
    Window::SetUp();

    // Get size of window so scaling works properly.
    GetSize();

    AddObject({std::make_shared<CheckBox>(*this,
                                          "Automatically connect to PSP/Vita networks",
                                          ScaleAutoConnectCheckBox,
                                          GetModel().mAutoDiscoverPSPVitaNetworks)});

    // TODO: Add
    // AddObject({std::make_shared<CheckBox>(
    //    *this, "Use SSID from XLink Kai for connection", ScaleXLinkSSIDCheckBox, GetModel().mUseSSIDFromXLinkKai)});

    AddObject({std::make_shared<CheckBox>(
        *this, "Use SSID from host broadcast", ScaleHostSSIDCheckBox, GetModel().mUseSSIDFromHost)});

    AddObject({std::make_shared<TextField>(*this,
                                           "Reconnect after network has been inactive for (seconds)",
                                           ScaleReConnectionTimeOutTextField,
                                           GetModel().mReConnectionTimeOutS,
                                           4,
                                           true,
                                           false,
                                           std::vector<char>())});

    auto lAdapterRadioBoxGroup{std::make_shared<RadioBoxGroup>(
        *this, "Use the following adapter:", ScaleUseWifiAdapterRadioBoxGroup, GetModel().mWifiAdapterSelection)};

    for (auto& lAdapter : GetModel().mWifiAdapterList) {
        lAdapterRadioBoxGroup->AddRadioBox(lAdapter.second);
    }

    // Objects need to be added for them to be drawn
    AddObject(lAdapterRadioBoxGroup);
    AddObject(CreateNextButton(*this, GetModel(), GetHeightReference(), GetWidthReference()));
    AddObject(CreateWizardStepText(*this, 2, 3, GetWidthReference()));
    AddObject(CreateQuitText(*this, GetHeightReference()));
}

void PromiscuousOptionsStep::Draw()
{
    // If autoconnect checkbox is checked, then show these sub-options
    GetObjects().at(1)->SetVisible(std::dynamic_pointer_cast<CheckBox>(GetObjects().at(0))->IsChecked());
    GetObjects().at(2)->SetVisible(std::dynamic_pointer_cast<CheckBox>(GetObjects().at(0))->IsChecked());

    Window::Draw();
}
