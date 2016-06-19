//
// Created by PyMba86 on 25.05.2016.
//

#ifndef LABWORK_EDITABLELIST_HPP
#define LABWORK_EDITABLELIST_HPP


#include <vaca/vaca.h>

#include "resource.h"
#include "LogoWidget.h"

using namespace vaca;

namespace MyWidget
{
    class EditableListBox : public ListBox
    {
        TextEdit* m_edit;
        int m_editingItem;

    public:

        EditableListBox(Widget* parent)
                : ListBox(parent)
        {
            m_edit = nullptr;
        }

    protected:

        virtual void onKeyDown(KeyEvent &ev)
        {
            ListBox::onKeyDown(ev);
            if (ev.getKeyCode() == Keys::Enter) {
                beginEdit(getSelectedItem());
                ev.consume();
            }
        }

        // When the user double-clicks in a item of the ListBox
        virtual void onItemDoubleClick(Event &ev)
        {
            ListBox::onItemDoubleClick(ev);
            beginEdit(getSelectedItem());
        }

        virtual void onResize(ResizeEvent& ev)
        {
            endEdit();
            ListBox::onResize(ev);
        }

        virtual void onScroll(ScrollEvent& ev)
        {
            ListBox::onScroll(ev);
            endEdit();
        }

    private:

        void onEditKeyDown(KeyEvent &ev)
        {
            if (ev.getKeyCode() == Keys::Enter)
                onEditFocusLeave();
        }

        void onEditFocusLeave()
        {
            endEdit();
        }

        void beginEdit(int index)
        {
            if (index >= 0 && m_edit == nullptr) {
                // create an Edit widget without client-edge
                m_edit = new TextEdit(getItemText(index), this, TextEdit::Styles::Default -
                                                                Widget::Styles::ClientEdge);
                m_edit->KeyDown.connect(&EditableListBox::onEditKeyDown, this);
                m_edit->FocusLeave.connect(Bind(&EditableListBox::onEditFocusLeave, this));
                m_edit->selectAll();
                m_edit->requestFocus();

                m_editingItem = index;

                layoutEdit();
            }
        }

        void endEdit()
        {
            if (m_edit != nullptr) {
                // we need to reset the m_edit variable to avoid calling two
                // times this destruction process because...
                int editingItem = m_editingItem;
                TextEdit *edit = m_edit;
                m_edit = nullptr;

                // ...this could produce a "onBeforeBoundsChange" event
                setItemText(editingItem, edit->getText());

                // delete the edit control
                delete_widget(edit);
            }
        }

        void layoutEdit()
        {
            m_edit->setBounds(getItemBounds(m_editingItem));
        }

    };

}

#endif //LABWORK_EDITABLELIST_HPP
