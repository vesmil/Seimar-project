#ifndef SUBMENUITEM_H
#define SUBMENUITEM_H

#include <vector>
#include <memory>
#include <qpushbutton.h>
#include <QLabel>

#include "itembase.h"

//! \brief Menu element from which next menu will be opened
class SubmenuItem : public ItemBase
{
public:
    /*!
     * \param text Text displayed in menu
     * \param parentMenu Parent menu to go when going back
     * \param parentWidget Parent widget as for all Qt widgets
     */
    SubmenuItem(QString text, SubmenuItem *parentMenu, QWidget *parent = nullptr);

    void execute() override;
    void control(QKeyEvent* event) override;

    bool isHidden() override;

    //! \brief Adds new item to the end of the menu
    void addItem(std::unique_ptr<ItemBase> item);

    //! \brief Displays menu in \a layout
    void display(QLayout* layout);

    //! \brief Hides all elements and removes them from \a layout
    void close(QLayout* layout);

private:
    void moveUp();
    void moveDown();
    void goBack();

    QLabel* m_text;

    size_t m_currentElement = 0;
    std::vector<std::unique_ptr<ItemBase>> m_itemList {};
};

#endif // SUBMENUITEM_H
