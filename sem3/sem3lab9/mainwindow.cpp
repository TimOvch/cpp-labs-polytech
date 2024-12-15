#include <QDebug>
#include "QRandomGenerator"
#include <QColor>
#include <QSqlError>
#include <QSet>
#include <QCheckBox>
#include <QFrame>
#include <QLabel>

#include "mainwindow.h"

QColor getRandomColor(){
    int red = 128 + QRandomGenerator::global()->bounded(100);
    int green = 128 + QRandomGenerator::global()->bounded(100);
    int blue = 128 + QRandomGenerator::global()->bounded(100);
    return QColor(red, green, blue);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    resize(1480, 920);

    ellipseCount = 0;
    rectCount = 0;
    triangleCount = 0;
    markActive = 0;

    QPushButton *addRectangleButton = new QPushButton("Добавить Прямоугольник", this);
    QPushButton *addEllipseButton = new QPushButton("Добавить Эллипс", this);
    QPushButton *addTriangleButton = new QPushButton("Добавить Треугольник", this);
    QPushButton *relateChoosen = new QPushButton("Соединить Выбранные", this);
    QPushButton *disconnectChoosen = new QPushButton("Отсоединить 2 Выбранных элемента", this);
    QPushButton *deleteSelectedButton = new QPushButton("Удалить Выбранные", this);
    markSelected = new QPushButton("Выделить все соединеия", this);
    filterOption = new QComboBox();
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    QFrame *line2 = new QFrame();
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);
    QFrame *line3 = new QFrame();
    line3->setFrameShape(QFrame::HLine);
    line3->setFrameShadow(QFrame::Sunken);
    QPushButton *submitFilter = new QPushButton("Применить фильтр", this);
    QPushButton *clearFilter = new QPushButton("Очистить фильтр", this);
    QPushButton *ghost1 = new QPushButton("", this);
    ghost1->setStyleSheet("background-color: rgba(255, 0, 0, 0); color: white;");

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    filterOption->addItems({"Только прямоугольники", "Только эллипсы", "Только треугольники"});

    tableView = new QTableView(this);
    tableView->resize(1480,300);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("shapes.db");

    if (!db.open()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к базе данных.");
        return;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS shapes ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "type TEXT NOT NULL, "
               "related_ids TEXT, "
               "type_count INTEGER NOT NULL, "
               "pos_x REAL NOT NULL, "
               "pos_y REAL NOT NULL, "
               "color_rgb TEXT NOT NULL"
               ");");

    model = new QSqlTableModel(this, db);
    model->setTable("shapes");
    model->select();

    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    tableView->setModel(model);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::MultiSelection);

    graphics = new ShapesGraphics(centralWidget);
    graphics->resize(1480,620);


    QWidget* buttons = new QWidget(this);
    buttons->setFixedSize(700,300);
    QVBoxLayout* buttonsLayot1 = new QVBoxLayout;
    buttonsLayot1->setSpacing(20);
    QVBoxLayout* buttonsLayot2 = new QVBoxLayout;
    buttonsLayot2->setSpacing(20);
    QVBoxLayout* buttonsLayot3 = new QVBoxLayout;
    buttonsLayot3->setSpacing(20);
    QHBoxLayout* mainButtonsLayout = new QHBoxLayout;

    QLabel* label1 = new QLabel("Добавление и удаление");
    label1->setAlignment(Qt::AlignHCenter);
    buttonsLayot1->addWidget(label1, 0, Qt::AlignTop);
    buttonsLayot1->addWidget(addRectangleButton, 0, Qt::AlignTop);
    buttonsLayot1->addWidget(addEllipseButton, 0, Qt::AlignTop);
    buttonsLayot1->addWidget(addTriangleButton, 0, Qt::AlignTop);
    buttonsLayot1->addWidget(deleteSelectedButton, 0, Qt::AlignTop);

    QLabel* label2 = new QLabel("Соединения");
    label2->setAlignment(Qt::AlignHCenter);
    buttonsLayot2->addWidget(label2, 0, Qt::AlignTop);
    buttonsLayot2->addWidget(relateChoosen, 0, Qt::AlignTop);
    buttonsLayot2->addWidget(disconnectChoosen, 0, Qt::AlignTop);
    buttonsLayot2->addWidget(markSelected, 0, Qt::AlignTop);
    buttonsLayot2->addWidget(ghost1, 0, Qt::AlignTop);

    QLabel* label3 = new QLabel("Фильтр");
    label3->setAlignment(Qt::AlignHCenter);
    buttonsLayot3->addWidget(label3, 0, Qt::AlignTop);
    buttonsLayot3->addWidget(filterOption, 0, Qt::AlignTop);
    buttonsLayot3->addWidget(submitFilter, 0, Qt::AlignTop);
    buttonsLayot3->addWidget(clearFilter, 0, Qt::AlignTop);
    buttonsLayot3->addWidget(ghost1, 0, Qt::AlignTop);

    mainButtonsLayout->addLayout(buttonsLayot1);
    mainButtonsLayout->addLayout(buttonsLayot2);
    mainButtonsLayout->addLayout(buttonsLayot3);

    buttons->setLayout(mainButtonsLayout);

    QWidget* tableAndButtons = new QWidget(this);
    tableAndButtons->setFixedSize(1480,300);
    QHBoxLayout* tableAndButtonsLayout = new QHBoxLayout;

    tableAndButtonsLayout->addWidget(tableView);
    tableAndButtonsLayout->addWidget(buttons);

    tableAndButtons->setLayout(tableAndButtonsLayout);

    QVBoxLayout* centralLayout = new QVBoxLayout;

    centralLayout->addWidget(tableAndButtons);
    centralLayout->addWidget(graphics);

    centralWidget->setLayout(centralLayout);


    connect(addRectangleButton, &QPushButton::clicked, this, &MainWindow::addRectangle);
    connect(addEllipseButton, &QPushButton::clicked, this, &MainWindow::addEllipse);
    connect(addTriangleButton, &QPushButton::clicked, this, &MainWindow::addTriangle);
    connect(deleteSelectedButton, &QPushButton::clicked, this, &MainWindow::deleteSelected);
    connect(relateChoosen, &QPushButton::clicked, this, &MainWindow::relateSelected);
    connect(disconnectChoosen, &QPushButton::clicked, this, &MainWindow::detachSelectedFromAll);
    connect(submitFilter, &QPushButton::clicked, this, &MainWindow::startFilter);
    connect(clearFilter, &QPushButton::clicked, this, &MainWindow::unFilter);
    connect(markSelected, &QPushButton::clicked, this, &MainWindow::markRelated);
    connect(graphics , &ShapesGraphics::posChanged, this, &MainWindow::posChanged);

    tableView->setItemDelegate(new ColorDelegate);

    filterActive = 0;

    drawExisting();
}

MainWindow::~MainWindow() {
     db.close();
}

void MainWindow::addShape(const QString &type, int &count) {
    QSqlQuery query;
    QColor color = getRandomColor();
    count++;

    query.prepare("INSERT INTO shapes (type, related_ids, type_count, pos_x, pos_y, color_rgb) VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(type);
    query.addBindValue("");
    query.addBindValue(count);
    query.addBindValue(0);
    query.addBindValue(0);
    query.addBindValue(QString("%1,%2,%3").arg(color.red()).arg(color.green()).arg(color.blue()));

    if (query.exec()) {
        int lastInsertId = query.lastInsertId().toInt();

        if (type == "Rectangle") {
            graphics->addRect(lastInsertId, color);
        } else if (type == "Ellipse") {
            graphics->addEllipse(lastInsertId, color);
        } else if (type == "Triangle") {
            graphics->addTriangle(lastInsertId, color);
        }

        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE shapes SET type_count = :newCount WHERE type = :type");
        updateQuery.bindValue(":newCount", count);
        updateQuery.bindValue(":type", type);

        if (!updateQuery.exec()) {
            QMessageBox::warning(this, "Ошибка", QString("Не удалось обновить счетчик для %1:\n%2").arg(type).arg(updateQuery.lastError().text()));
        }
    } else {
        QMessageBox::warning(this, "Ошибка", QString("Не удалось добавить %1:\n%2").arg(type).arg(query.lastError().text()));
    }

    model->select();
}

void MainWindow::collectRelatedIds(int id, QSet<int> &idsToDelete) {
    idsToDelete.insert(id);

    QSqlQuery query;
    query.prepare("SELECT related_ids FROM shapes WHERE id = ?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        QString relatedIds = query.value(0).toString();
        if (!relatedIds.isEmpty()) {
            for (const QString &relatedId : relatedIds.split(",")) {
                int relatedIdInt = relatedId.toInt();
                if (!idsToDelete.contains(relatedIdInt)) {
                    collectRelatedIds(relatedIdInt, idsToDelete);
                }
            }
        }
    }
}

void MainWindow::drawExisting()
{
    QSqlQuery query(db);

    if (!query.exec("SELECT * FROM shapes")) {
        qDebug() << "Ошибка при выполнении запроса:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        QString type = query.value("type").toString();
        int typeCount = query.value("type_count").toInt();
        int posX = query.value("pos_x").toReal();
        int posY = query.value("pos_y").toReal();
        QString colorString = query.value("color_rgb").toString();
        QColor color;

        if(type == "Rectangle"){
            rectCount = typeCount;
        } else if(type == "Ellipse") {
            ellipseCount = typeCount;
        } else if (type == "Triangle"){
            triangleCount = typeCount;
        }

        QStringList rgbValues = colorString.split(",", Qt::SkipEmptyParts);

        if (rgbValues.size() == 3) {
            bool ok1, ok2, ok3;
            int red = rgbValues[0].toInt(&ok1);
            int green = rgbValues[1].toInt(&ok2);
            int blue = rgbValues[2].toInt(&ok3);

            if (ok1 && ok2 && ok3 &&
                red >= 0 && red <= 255 &&
                green >= 0 && green <= 255 &&
                blue >= 0 && blue <= 255) {
                color = QColor(red, green, blue);
            }
        }

        if (type == "Rectangle"){
            graphics->addRect(id, color,posX,posY);
        } else if (type == "Ellipse") {
            graphics->addEllipse(id,color,posX,posY);
        } else if (type == "Triangle"){
            graphics->addTriangle(id, color,posX,posY);
        }
    }

    if (!query.exec("SELECT * FROM shapes")) {
        qDebug() << "Ошибка при выполнении запроса:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        QString relatedIds = query.value("related_ids").toString();

        QStringList idList = relatedIds.split(",", Qt::SkipEmptyParts);

        for (const QString &idS : idList) {
            bool ok;
            int idValue = idS.toInt(&ok);
            if (ok) {
                graphics->addRelation(id,idValue);
            }
        }
    }
}

void MainWindow::addRectangle() {
    addShape("Rectangle", rectCount);
}

void MainWindow::addEllipse() {
    addShape("Ellipse", ellipseCount);
}

void MainWindow::addTriangle() {
    addShape("Triangle", triangleCount);
}

void MainWindow::deleteSelected() {
    QModelIndexList selectedRows = tableView->selectionModel()->selectedRows();

    if (selectedRows.isEmpty()) {
        QMessageBox::information(this, "Информация", "Нет выбранных элементов для удаления.");
        return;
    }

    if (QMessageBox::question(this, "Подтверждение", "Удалить выбранные элементы?") == QMessageBox::No) {
        return;
    }

    QSet<int> idsToDelete;

    for (const QModelIndex &index : selectedRows) {
        int id = model->data(model->index(index.row(), 0)).toInt();
        collectRelatedIds(id, idsToDelete);
    }

    for (int id : idsToDelete) {
        graphics->deleteItem(id);

        QSqlQuery query2;
        query2.prepare("SELECT type FROM shapes WHERE id = :id_param");
        query2.bindValue(":id_param", id);

        if (query2.exec()) {
            if (query2.next()) {
                QString shapeType = query2.value(0).toString();

                if(shapeType == "Ellipse"){
                    ellipseCount--;
                } else if (shapeType == "Rectangle"){
                    rectCount--;
                } else if(shapeType == "Triangle"){
                    triangleCount--;
                }
            }
        }

        QSqlQuery query;
        query.prepare("DELETE FROM shapes WHERE id = ?");
        query.addBindValue(id);

        if (!query.exec()) {
            QMessageBox::warning(this, "Ошибка", "Не удалось удалить элементы. " + query.lastError().text());
        }
    }

    model->submitAll();
    model->select();
}

void MainWindow::relateSelected()
{
    QModelIndexList selectedRows = QModelIndexList();
    selectedRows = tableView->selectionModel()->selectedRows();

    if (selectedRows.isEmpty()) {
        QMessageBox::information(this, "Ошибка", "Нет выбранных элементов для соединения.");
        return;
    } else if(selectedRows.length() == 1){
        QMessageBox::information(this, "Ошибка", "Вы выбрали только один элемент для соединения.");
        return;
    }

    if(filterActive){
        QMessageBox::information(this, "Ошибка", "Нельзя производить соединения с активным фильтром.");
        return;
    }

    QVector<int> selectedIds;
    for (const QModelIndex &index : selectedRows) {
        int id = model->data(model->index(index.row(), 0)).toInt();
        selectedIds.append(id);
    }

    for (const QModelIndex &index : selectedRows) {
        int id = model->data(model->index(index.row(), 0)).toInt();

        QSqlQuery query;
        query.prepare("SELECT related_ids FROM shapes WHERE id = ?");
        query.addBindValue(id);

        if (query.exec() && query.next()) {
            QString existingRelatedIds = query.value(0).toString();

            QSet<int> existingIds;
            if (!existingRelatedIds.isEmpty()) {
                for (const QString &existingId : existingRelatedIds.split(",")) {
                    existingIds.insert(existingId.toInt());
                }
            }

            for (int newId : selectedIds) {
                if (newId != id && !existingIds.contains(newId)) {
                    existingIds.insert(newId);
                }
            }

            QStringList uniqueIds;
            for (int uniqueId : existingIds) {
                uniqueIds.append(QString::number(uniqueId));
                graphics->addRelation(id,uniqueId);
            }
            QString updatedRelatedIds = uniqueIds.join(",");

            query.clear();
            query.prepare("UPDATE shapes SET related_ids = ? WHERE id = ?");
            query.addBindValue(updatedRelatedIds);
            query.addBindValue(id);

            if (!query.exec()) {
                QMessageBox::warning(this, "Ошибка", "Не удалось соединить элементы. " + query.lastError().text());
            }
        }
    }

    model->select();
}

void MainWindow::detachSelectedFromAll() {
    QModelIndexList selectedRows = tableView->selectionModel()->selectedRows();

    if (selectedRows.size() != 2) {
        QMessageBox::warning(this, "Предупреждение", "Пожалуйста, выберите ровно два элемента для отсоединения.");
        return;
    }

    int id1 = model->data(model->index(selectedRows[0].row(), 0)).toInt();
    int id2 = model->data(model->index(selectedRows[1].row(), 0)).toInt();

    QString relatedIds1;
    QString relatedIds2;

    QSqlQuery query;

    query.prepare("SELECT related_ids FROM shapes WHERE id = ?");
    query.addBindValue(id1);
    if (query.exec() && query.next()) {
        relatedIds1 = query.value(0).toString();
    }

    query.prepare("SELECT related_ids FROM shapes WHERE id = ?");
    query.addBindValue(id2);
    if (query.exec() && query.next()) {
        relatedIds2 = query.value(0).toString();
    }

    if (!relatedIds1.split(",").contains(QString::number(id2)) &&
        !relatedIds2.split(",").contains(QString::number(id1))) {
        QMessageBox::warning(this, "Ошибка", "Выбранные элементы не связаны.");
        return;
    }

    if (QMessageBox::question(this, "Подтверждение",
                              QString("Отсоединить элементы с ID %1 и %2?")
                                  .arg(id1).arg(id2)) == QMessageBox::No) {
        return;
    }

    QStringList idsList1 = relatedIds1.split(",", Qt::SkipEmptyParts);
    idsList1.removeAll(QString::number(id2));
    idsList1.removeAll(QString::number(id1));
    relatedIds1 = idsList1.join(",");

    QStringList idsList2 = relatedIds2.split(",", Qt::SkipEmptyParts);
    idsList2.removeAll(QString::number(id1));
    idsList2.removeAll(QString::number(id2));
    relatedIds2 = idsList2.join(",");

    query.prepare("UPDATE shapes SET related_ids = ? WHERE id = ?");
    query.addBindValue(relatedIds1);
    query.addBindValue(id1);

    if (!query.exec()) {
        QMessageBox::warning(this, "Ошибка",
                             QString("Не удалось обновить связи для элемента с ID %1:\n%2").arg(id1).arg(query.lastError().text()));
    }

    query.prepare("UPDATE shapes SET related_ids = ? WHERE id = ?");
    query.addBindValue(relatedIds2);
    query.addBindValue(id2);

    if (!query.exec()) {
        QMessageBox::warning(this, "Ошибка",
                             QString("Не удалось обновить связи для элемента с ID %1:\n%2").arg(id2).arg(query.lastError().text()));
    }

    graphics->deleteRelation(id1,id2);

    model->select();
}

void MainWindow::filterRects()
{
    QString str("Rectangle");
    typeFilter(str);
}

void MainWindow::filterEllipses()
{
    QString str("Ellipse");
    typeFilter(str);
}

void MainWindow::filterTriangles()
{
    QString str("Triangle");
    typeFilter(str);
}

void MainWindow::unFilter()
{
    graphics->showAll();

    model->setFilter("");
    model->select();

    filterActive = 0;
}

void MainWindow::typeFilter(QString &type)
{
    unFilter();
    QVector<int> ids;
    filterActive = 1;

    QSqlQuery query;
    query.prepare("SELECT id FROM shapes WHERE type != :type");
    query.bindValue(":type", type);

    if (query.exec()) {
        while (query.next()) {
            ids.append(query.value(0).toInt());
        }
    }

    for(int id:ids){
        graphics->hideItemFilter(id);
    }

    model->setFilter(QString("type == '%1'").arg(type));

    model->select();
}

void MainWindow::startFilter()
{
    int selectedIndex = filterOption->currentIndex();
    if(selectedIndex == 0){
        filterRects();
    } else if(selectedIndex == 1){
        filterEllipses();
    } else if(selectedIndex == 2){
        filterTriangles();
    }
}

void MainWindow::markRelated()
{
    if(markActive){
        graphics->unMarkAll();

        markActive = 0;

        markSelected->setText("Выделить все соединения");

    } else {

        QModelIndexList selectedRows = tableView->selectionModel()->selectedRows();

        if (selectedRows.isEmpty()) {
            QMessageBox::information(this, "Ошибка", "Нет выбранных элементов для выделения.");
            return;
        } else if(selectedRows.length() > 1){
            QMessageBox::information(this, "Ошибка", "Выберите только один элемент для выделения.");
            return;
        }

        QSet<int> idsToMark;

        for (const QModelIndex &index : selectedRows) {
            int id = model->data(model->index(index.row(), 0)).toInt();
            collectRelatedIds(id, idsToMark);
        }

        for(int id: idsToMark){
            graphics->markItem(id);
        }

        markActive = 1;

        markSelected->setText("Убрать выделение соединений");
    }
}

void MainWindow::posChanged(const int &id, const int& x, const int &y)
{
    QSqlQuery query(db);

    query.prepare("UPDATE shapes SET pos_x = :x, pos_y = :y WHERE id = :id");
    query.bindValue(":x", x);
    query.bindValue(":y", y);
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось обновить позицию.");
    }
    model->select();
    model->submitAll();
}


void ColorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {

    if(index.column() == 3){
        QString shapeType = index.model()->data(index.sibling(index.row(), 1)).toString();
        int value = index.model()->data(index.sibling(index.row(), 3)).toInt();

        int shapeCount = 0;

        if (value >= 1 && value <= 3) {
            shapeCount = 1;
        }
        else if (value >= 4 && value <= 10) {
            shapeCount = 2;
        }
        else if (value > 10) {
            shapeCount = 3;
        }

        int shapeSize = 20;
        int spacing = 10;

        for (int i = 0; i < shapeCount; ++i) {
            int x = option.rect.x() + (shapeSize + spacing) * i + (option.rect.width() - ((shapeSize + spacing) * shapeCount + spacing)) / 2;
            int y = option.rect.y() + (option.rect.height() - shapeSize) / 2;

            if (shapeType == QStringLiteral("Rectangle")) {
                painter->fillRect(x, y, shapeSize, shapeSize, QColor(0, 0, 255));
            }
            else if (shapeType == QStringLiteral("Ellipse")) {
                painter->setRenderHint(QPainter::Antialiasing);
                painter->setBrush(QColor(0, 255, 0));
                painter->drawEllipse(x, y, shapeSize, shapeSize);
            }
            else if (shapeType == QStringLiteral("Triangle")) {
                painter->setRenderHint(QPainter::Antialiasing);
                painter->setBrush(QColor(255, 0, 0));
                QPolygon triangle;
                triangle << QPoint(x, y + shapeSize)
                         << QPoint(x + shapeSize / 2, y)
                         << QPoint(x + shapeSize, y + shapeSize);
                painter->drawPolygon(triangle);
            }
        }
        return;

    }

    if(index.column() == 6){
        QString colorString = index.data().toString();

        QStringList rgbValues = colorString.split(',');
        if (rgbValues.size() == 3) {
            int r = rgbValues[0].toInt();
            int g = rgbValues[1].toInt();
            int b = rgbValues[2].toInt();

            QColor color(r, g, b);

            painter->setBrush(color);
            painter->fillRect(option.rect, color);
            painter->drawRect(option.rect);
        }
        return;
    }

    QStyledItemDelegate::paint(painter, option, index);
}
