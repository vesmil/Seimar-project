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
    SubmenuItem(QString text, SubmenuItem *parentMenu, QWidget *parent = nullptr);

    void executeSelected() override;
    void control(QKeyEvent* event) override;

    bool isHidden() override;

    void display();
    void close();

    QLabel* m_text;

    size_t m_currentElement = 0;
    std::vector<std::unique_ptr<ItemBase>> itemList {};
};

#endif // SUBMENUITEM_H
