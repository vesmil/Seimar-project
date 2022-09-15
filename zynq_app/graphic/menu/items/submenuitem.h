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

    void execute() override;
    void control(QKeyEvent* event) override;

    bool isHidden() override;

    void addItem(std::unique_ptr<ItemBase> item);

    void display(QLayout* layout);
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
