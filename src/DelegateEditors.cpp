/**********************************************************************
* File:        DelegateEditors.cpp
* Description: SpinBoxDelegate that export signals of SpinBox to QTableView
               Created based on Nokia Qt\4.7.3\examples\itemviews\
               spinboxdelegate
* Author:      Zdenko Podobny
* Created:     2011-07-06
*
* (C) Copyright 2011, Zdenko Podobny
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**    http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*
**********************************************************************/

#include "include/DelegateEditors.h"

/********************************
 * SpinBoxDelegate
 ********************************/
SpinBoxDelegate::SpinBoxDelegate(QObject *parent)
  : QItemDelegate(parent) {
}

QWidget *SpinBoxDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &/* option */,
                                       const QModelIndex &/* index */) const {
  QSpinBox *editor = new QSpinBox(parent);
  editor->setRange(0, 1000000);
  connect(editor, SIGNAL(valueChanged(int)), SIGNAL(sbd_valueChanged(int)));
  connect(editor, SIGNAL(editingFinished()), SIGNAL(sbd_editingFinished()));
  return editor;
}

void SpinBoxDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const {
  int value = index.model()->data(index, Qt::EditRole).toInt();

  QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
  spinBox->setValue(value);
}
void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const {
  QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
  spinBox->interpretText();
  int value = spinBox->value();
  model->setData(index, value, Qt::EditRole);
}

void SpinBoxDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const {
  editor->setGeometry(option.rect);
}
