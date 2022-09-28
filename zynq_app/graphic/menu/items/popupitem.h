#ifndef POPUPITEM_H
#define POPUPITEM_H

#include <QKeyEvent>

#include "library/controller/elements/popup.h"
#include "itembase.h"

//! \brief Item which will open a new window upon confirmation
class PopupItem : public ItemBase
{
public:
    /*!
     * \param text Text displayed in menu
     * \param popup Complex Popup object which will be used to open a new window
     * \param parentMenu Parent menu to go to after confirmation
     * @param parentWidget Parent widget as for all Qt widgets
     */
    PopupItem(const QString& text, ControlableWidget* popup, SubmenuItem* parentMenu, QWidget* parent);

    void execute() override;
    void control(QKeyEvent* event) override;

    ControlableWidget* m_popupWidget;
};

#endif // POPUPITEM_H
