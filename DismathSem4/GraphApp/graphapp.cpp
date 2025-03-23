#include "graphapp.h"

GraphApp::GraphApp(QWidget *parent) : QMainWindow(parent), activeGraphIndex(-1), graphsCount(0) {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);


    QToolBar *toolBar = new QToolBar("Инструменты", this);
    toolBar->setStyleSheet(
        "QToolButton {"
        "   background-color: black;"
        "   color: white;"
        "   padding: 10px;"
        "   border-radius: 5px;"
        "   box-shadow: 2px 2px 5px rgba(0, 0, 0, 0.3);"
        "}"
        "QToolButton:hover {"
        "   background-color: white;"
        "   color: black;"
        "}"
        );

    addToolBar(Qt::TopToolBarArea, toolBar);

    setupToolBar(toolBar, this);

    QHBoxLayout *upperLayout = new QHBoxLayout();

    graphInfoDisplay = new QTextEdit(this);
    graphInfoDisplay->setReadOnly(true);

    view = new GraphView(this);
    view->setMinimumSize(600, 600);
    upperLayout->addWidget(view);

    QTabWidget *tabWidget = new QTabWidget;
    connect(tabWidget,&QTabWidget::currentChanged, this,&GraphApp::tabChanged);
    tabWidget->setMinimumSize(600, 500);
    HighlightNonEmptyDelegate* delegate = new HighlightNonEmptyDelegate(this);
    adjacencyTable = new QTableWidget();
    adjacencyTable->setItemDelegate(delegate);
    adjacencyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    shimbellTable = new QTableWidget();
    shimbellTable->setItemDelegate(delegate);
    shimbellTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    weightsTable = new QTableWidget();
    weightsTable->setItemDelegate(delegate);
    weightsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    dijkstraTable = new QTableWidget();
    dijkstraTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(dijkstraTable, &QTableWidget::itemClicked, this, &GraphApp::onDijkstraTableClicked);
    tabWidget->addTab(adjacencyTable, "Матрица смежности");
    tabWidget->addTab(weightsTable, "Матрица весов");
    tabWidget->addTab(shimbellTable, "Метод Шимбелла");
    tabWidget->addTab(dijkstraTable, "Алгоритм Дейкстры");
    tabWidget->addTab(graphInfoDisplay, "Информация");

    upperLayout->addWidget(tabWidget);

    mainLayout->addLayout(upperLayout);
    setCentralWidget(centralWidget);

    setWindowTitle("GraphApp");
    setFixedSize(1400, 700);
}

GraphApp::~GraphApp()
{
    for (auto& graphP : graphs) {
        delete graphP;
    }
}

void GraphApp::setupToolBar(QToolBar *toolBar, GraphApp *app) {

    // ГЕНЕРАЦИЯ ГРАФА
    QToolButton *graphControlButton = new QToolButton(toolBar);
    graphControlButton->setText("Генерация");
    QMenu *graphControlMenu = new QMenu(graphControlButton);
    graphControlMenu->setStyleSheet(
        "QMenu { padding: 10px; }"
        "QMenu::item { padding: 10px 10px; }"
        );

    QWidgetAction *graphTypeAction = new QWidgetAction(graphControlMenu);
    graphTypeCombo = new QComboBox();
    graphTypeCombo->addItems({"Ориентированный"});
    graphTypeAction->setDefaultWidget(graphTypeCombo);
    graphControlMenu->addAction(graphTypeAction);

    QWidgetAction *verticesAction = new QWidgetAction(graphControlMenu);
    verticesSpin = new QSpinBox();
    verticesSpin->setRange(2, 100);
    verticesAction->setDefaultWidget(verticesSpin);
    graphControlMenu->addAction(verticesAction);

    QWidgetAction *negativeWeightsAction = new QWidgetAction(graphControlMenu);
    negativeWeightsCheckBox = new QCheckBox("Разрешить отрицательные веса", this);
    negativeWeightsAction->setDefaultWidget(negativeWeightsCheckBox);
    graphControlMenu->addAction(negativeWeightsAction);

    QAction *generateAction = new QAction("Генерировать", graphControlMenu);
    connect(generateAction, &QAction::triggered, app, &GraphApp::generateGraph);
    graphControlMenu->addAction(generateAction);

    graphControlButton->setMenu(graphControlMenu);
    graphControlButton->setPopupMode(QToolButton::InstantPopup);
    toolBar->addWidget(graphControlButton);



    // МЕТОД ШИМБЕЛЛА
    QToolButton *shimbellButton = new QToolButton(toolBar);
    shimbellButton->setText("Шимбелл");
    QMenu *shimbellMenu = new QMenu(shimbellButton);
    shimbellMenu->setStyleSheet(
        "QMenu { padding: 10px; }"
        "QMenu::item { padding: 10px 10px; }"
        );

    QWidgetAction *shimbellTypeAction = new QWidgetAction(shimbellMenu);
    shimbellCombo = new QComboBox();
    shimbellCombo->addItems({"Min", "Max"});
    shimbellTypeAction->setDefaultWidget(shimbellCombo);
    shimbellMenu->addAction(shimbellTypeAction);

    QWidgetAction *shimbellSpinAction = new QWidgetAction(shimbellMenu);
    shimbellSpin = new QSpinBox();
    shimbellSpin->setRange(1, 100);
    shimbellSpinAction->setDefaultWidget(shimbellSpin);
    shimbellMenu->addAction(shimbellSpinAction);

    QAction *shimbellMethodAction = new QAction("Метод Шимбелла", shimbellMenu);
    connect(shimbellMethodAction, &QAction::triggered, app, &GraphApp::shimbellMethod);
    shimbellMenu->addAction(shimbellMethodAction);

    shimbellButton->setMenu(shimbellMenu);
    shimbellButton->setPopupMode(QToolButton::InstantPopup);
    toolBar->addWidget(shimbellButton);



    // ПОИСК ПУТЕЙ
    QToolButton *pathControlButton = new QToolButton(toolBar);
    pathControlButton->setText("Поиск маршрутов");
    QMenu *pathControlMenu = new QMenu(pathControlButton);
    pathControlMenu->setStyleSheet(
        "QMenu { padding: 10px; }"
        "QMenu::item { padding: 10px 10px; }"
        );

    QWidgetAction *startVertexAction = new QWidgetAction(pathControlMenu);
    startVertexSpin = new QSpinBox();
    startVertexSpin->setRange(1, 50);
    startVertexAction->setDefaultWidget(startVertexSpin);
    pathControlMenu->addAction(startVertexAction);

    QWidgetAction *endVertexAction = new QWidgetAction(pathControlMenu);
    endVertexSpin = new QSpinBox();
    endVertexSpin->setRange(1, 50);
    endVertexAction->setDefaultWidget(endVertexSpin);
    pathControlMenu->addAction(endVertexAction);

    QAction *findPathsAction = new QAction("Найти пути", pathControlMenu);
    connect(findPathsAction, &QAction::triggered, app, &GraphApp::findPaths);
    pathControlMenu->addAction(findPathsAction);

    pathControlButton->setMenu(pathControlMenu);
    pathControlButton->setPopupMode(QToolButton::InstantPopup);
    toolBar->addWidget(pathControlButton);

    // DFS по ребрам
    QToolButton *dfsButton = new QToolButton(toolBar);
    dfsButton->setText("Обход ребер в глубину");
    QMenu *dfsControlMenu = new QMenu(dfsButton);
    dfsControlMenu->setStyleSheet(
        "QMenu { padding: 10px; }"
        "QMenu::item { padding: 10px 10px; }"
        );

    QWidgetAction *startDFSAction = new QWidgetAction(dfsControlMenu);
    startDfsSpin = new QSpinBox();
    startDfsSpin->setRange(1, 50);
    startDFSAction->setDefaultWidget(startDfsSpin);
    dfsControlMenu->addAction(startDFSAction);

    QWidgetAction *endDFSAction = new QWidgetAction(dfsControlMenu);
    endDfsSpin = new QSpinBox();
    endDfsSpin->setRange(1, 50);
    endDFSAction->setDefaultWidget(endDfsSpin);
    dfsControlMenu->addAction(endDFSAction);

    QAction *showDFSAction = new QAction("Запустить обход", dfsControlMenu);
    connect(showDFSAction, &QAction::triggered, app, &GraphApp::edgesDFS);
    dfsControlMenu->addAction(showDFSAction);

    dfsButton->setMenu(dfsControlMenu);
    dfsButton->setPopupMode(QToolButton::InstantPopup);
    toolBar->addWidget(dfsButton);


    //АЛГОРИТМ ДЕЙКСТРЫ
    QToolButton *dijkstraButton = new QToolButton(toolBar);
    dijkstraButton->setText("Алгоритм Дейкстры");
    QMenu *dijkstraMenu = new QMenu(dijkstraButton);
    dijkstraMenu->setStyleSheet(
        "QMenu { padding: 10px; }"
        "QMenu::item { padding: 10px 10px; }"
        );

    QWidgetAction *dijkstraAction = new QWidgetAction(dijkstraMenu);
    dijkstraSpin = new QSpinBox();
    dijkstraSpin->setRange(1, 50);
    dijkstraAction->setDefaultWidget(dijkstraSpin);
    dijkstraMenu->addAction(dijkstraAction);

    QWidgetAction *negativeDijkstraAction = new QWidgetAction(dijkstraMenu);
    negativedijkstraCheckBox = new QCheckBox("С отрицательными весами", this);
    negativeDijkstraAction->setDefaultWidget(negativedijkstraCheckBox);
    dijkstraMenu->addAction(negativeDijkstraAction);

    QAction *dijkstraStartAction = new QAction("Запустить", dijkstraMenu);
    connect(dijkstraStartAction, &QAction::triggered, app, &GraphApp::dijkstraAlgorithm);
    dijkstraMenu->addAction(dijkstraStartAction);

    dijkstraButton->setMenu(dijkstraMenu);
    dijkstraButton->setPopupMode(QToolButton::InstantPopup);
    toolBar->addWidget(dijkstraButton);



    // ФАЙЛЫ
    QToolButton *fileControlButton = new QToolButton(toolBar);
    fileControlButton->setText("Файл");
    QMenu *fileControlMenu = new QMenu(fileControlButton);
    fileControlMenu->setStyleSheet(
        "QMenu { padding: 10px; }"
        "QMenu::item { padding: 10px 10px; }"
        );

    QAction *openAction = new QAction("Открыть из файла", fileControlMenu);
    connect(openAction, &QAction::triggered, app, &GraphApp::loadGraphFromFile);
    fileControlMenu->addAction(openAction);

    QAction *saveAction = new QAction("Сохранить в файл", fileControlMenu);
    connect(saveAction, &QAction::triggered, app, &GraphApp::saveGraphToFile);
    fileControlMenu->addAction(saveAction);

    fileControlButton->setMenu(fileControlMenu);
    fileControlButton->setPopupMode(QToolButton::InstantPopup);
    toolBar->addWidget(fileControlButton);
}

void GraphApp::refactorSpinBoxes()
{
    shimbellSpin->setRange(1,graphs[activeGraphIndex]->getP());
    startVertexSpin->setRange(1,graphs[activeGraphIndex]->getP());
    endVertexSpin->setRange(1,graphs[activeGraphIndex]->getP());
    startDfsSpin->setRange(1,graphs[activeGraphIndex]->getP());
    endDfsSpin->setRange(1,graphs[activeGraphIndex]->getP());
    dijkstraSpin->setRange(1,graphs[activeGraphIndex]->getP());
}

void GraphApp::generateGraph()
{
    graphsCount++;
    if(graphTypeCombo->currentIndex() == 0){
        AbstractGraph* newGraph = new OrientedGraph(verticesSpin->value(),negativeWeightsCheckBox->isChecked());
        newGraph->setName("Новый граф");
        newGraph->acycleGraphGenerate();
        graphs.push_back(newGraph);
        activeGraphIndex = graphs.size()-1;
        changeActiveGraph(activeGraphIndex);
    } else if(graphTypeCombo->currentIndex() == 1){
        // Неориентированный
    }
}

void GraphApp::changeActiveGraph(const int &newActiveGraphIndex)
{
    activeGraphIndex = newActiveGraphIndex;
    changeTable(adjacencyTable,(graphs[activeGraphIndex])->getAdjacency().getData());
    changeTable(shimbellTable,(graphs[activeGraphIndex])->getWeights().getData());
    changeTable(weightsTable,(graphs[activeGraphIndex])->getWeights().getData());
    dijkstraIterations = 0;
    dijkstraWithNegIterations = 0;
    changeInfo();
    view->setAdjacencyMatrix((graphs[activeGraphIndex])->getWeights().getData(),1);
    refactorSpinBoxes();
}

void GraphApp::changeTable(QTableWidget *table, const QVector<QVector<int> > &matrix)
{
    if (matrix.isEmpty()) {
        table->clear();
        return;
    }

    int rowCount = matrix.size();
    int colCount = matrix[0].size();

    table->setRowCount(rowCount);
    table->setColumnCount(colCount);

    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(matrix[row][col]));
            item->setTextAlignment(Qt::AlignCenter);
            table->setItem(row, col, item);
        }
    }

    table->resizeColumnsToContents();
    table->resizeRowsToContents();

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void GraphApp::changeInfo()
{
    AbstractGraph* activeGraph = graphs[activeGraphIndex];
    QString info = QString(
                       "<div style='padding: 10px;'>"
                       "<h1 style='margin-bottom: 20px;'>Информация о графе</h1>"
                       "<table style='width: 100%; border-collapse: collapse;'>"
                       "<tr><td style='padding: 5px; width: 40%;'><b>Количество вершин:</b></td><td style='padding: 5px;'>%1</td></tr>"
                       "<tr><td style='padding: 5px; width: 40%;'><b>Количество ребер:</b></td><td style='padding: 5px;'>%2</td></tr>"
                       "<tr><td style='padding: 5px; width: 40%;'><b>Тип графа:</b></td><td style='padding: 5px;'>%3</td></tr>"
                       "<tr><td style='padding: 5px; width: 40%;'><b>Ациклический:</b></td><td style='padding: 5px;'>%4</td></tr>"
                       "<tr><td style='padding: 5px; width: 40%;'><b>Связный:</b></td><td style='padding: 5px;'>%5</td></tr>"
                       "<tr><td style='padding: 5px; width: 40%;'><b>Отрицательные веса:</b></td><td style='padding: 5px;'>%6</td></tr>"
                       "<tr><td style='padding: 5px; width: 40%;'><b>Итерации Дейкстры:</b></td><td style='padding: 5px;'>%7</td></tr>"
                       "<tr><td style='padding: 5px; width: 40%;'><b>Итерации Дейкстры с отр. весами:</b></td><td style='padding: 5px;'>%8</td></tr>"
                       "</table>"
                       "</div>"
                       )
                       .arg(activeGraph->getP())
                       .arg(activeGraph->getQ())
                       .arg(activeGraph->getType())
                       .arg(activeGraph->getAcycle() ? "Да" : "Нет")
                       .arg(activeGraph->getConnected() ? "Да" : "Нет")
                       .arg(activeGraph->getNegativeWeights() ? "Да" : "Нет")
                       .arg(dijkstraIterations)
                       .arg(dijkstraWithNegIterations);

    graphInfoDisplay->setText(info);
}

void GraphApp::tabChanged(int index)
{
    view->clearHighlightedPath();
}


void GraphApp::saveGraphToFile() {
    if (graphsCount != 0) {
        AbstractGraph* activeGraph = graphs[activeGraphIndex];
        QString fileName = QFileDialog::getSaveFileName(
            this,
            "Сохранить граф",
            "",
            "Text files (*.txt)"
            );

        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);

                out << activeGraph->getName() << "\n";

                if (dynamic_cast<OrientedGraph*>(activeGraph)) {
                    out << "Oriented\n";
                } else if (dynamic_cast<UnorientedGraph*>(activeGraph)) {
                    out << "Unoriented\n";
                }

                out << activeGraph->getP() << "\n";
                out << activeGraph->getNegativeWeights() << "\n";

                QVector<QVector<int>> matrix = activeGraph->getAdjacency().getData();
                for (const auto& row : matrix) {
                    for (int val : row) {
                        out << val << " ";
                    }
                    out << "\n";
                }

                file.close();
                QMessageBox::information(
                    this,
                    "Успех",
                    QString("Граф '%1' успешно сохранён в файл: %2").arg(activeGraph->getName(), fileName)
                    );
            } else {
                QMessageBox::critical(
                    this,
                    "Ошибка",
                    "Не удалось открыть файл для записи."
                    );
            }
        } else {
            QMessageBox::warning(
                this,
                "Отмена",
                "Сохранение отменено."
                );
        }
    } else {
        QMessageBox::warning(
            this,
            "Предупреждение",
            "Нет активного графа для сохранения."
            );
    }
}

void GraphApp::loadGraphFromFile() {
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Загрузить граф",
        "",
        "Text files (*.txt)"
        );

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString graphName = in.readLine();
            QString graphType = in.readLine();
            int verticesCount = in.readLine().toInt();
            bool neg = in.readLine().toInt();


            QVector<QVector<int>> matrix;
            for (int i = 0; i < verticesCount; ++i) {
                QStringList rowValues = in.readLine().split(" ", Qt::SkipEmptyParts);
                QVector<int> row;
                for (const QString& val : rowValues) {
                    row.push_back(val.toInt());
                }
                matrix.push_back(row);
            }

            file.close();


            AbstractGraph* newGraph = nullptr;
            if (graphType == "Oriented") {
                newGraph = new OrientedGraph(verticesCount,neg);
            } else if (graphType == "Unoriented") {
                newGraph = new UnorientedGraph(verticesCount);
            }

            if (newGraph) {
                newGraph->loadAdjacency(Matrix(matrix));
                newGraph->setName(graphName);
                graphs.push_back(newGraph);
                activeGraphIndex = graphs.size() - 1;
                changeActiveGraph(activeGraphIndex);
                qDebug() << "Граф загружен из файла:" << fileName;
                graphsCount++;
            } else {
                qDebug() << "Неизвестный тип графа.";
            }
        } else {
            qDebug() << "Ошибка при открытии файла для чтения.";
        }
    } else {
        qDebug() << "Загрузка отменена.";
    }
}

void GraphApp::shimbellMethod()
{
    if(graphsCount==0){
        QMessageBox::critical(
            this,
            "Ошибка",
            "Нет активного графа."
            );
        return;
    }

    QVector<QVector<int>> matrix = (graphs[activeGraphIndex]->shimbellMethod(shimbellSpin->value()-1, shimbellCombo->currentIndex())).getData();

    changeTable(shimbellTable,matrix);
}

void GraphApp::findPaths() {
    if (activeGraphIndex == -1) {
        QMessageBox::warning(this, "Ошибка", "Граф не сгенерирован.");
        return;
    }

    int start = startVertexSpin->value();
    int end = endVertexSpin->value();

    if (start > graphs[activeGraphIndex]->getAdjacency().getRows() || end > graphs[activeGraphIndex]->getAdjacency().getRows()) {
        QMessageBox::warning(this, "Ошибка", "Номера вершин больше количества вершин графа.");
        return;
    }

    QPair<int, QVector<QVector<int>>> result = graphs[activeGraphIndex]->countPathsBFS(start-1,end-1);

    if (result.first > 0) {
        PathsDialog *dialog = new PathsDialog(result.second, this);
        connect(dialog, &PathsDialog::pathSelected, this, &GraphApp::handlePathSelected);
        dialog->exec();
        view->clearHighlightedPath();
    } else {
        QMessageBox::information(this, "Информация", "Пути не найдены.");
    }

}

void GraphApp::handlePathSelected(const QVector<int> &path)
{
    view->highlightPath(path);
}

void GraphApp::edgesDFS()
{
    if (activeGraphIndex == -1) {
        QMessageBox::warning(this, "Ошибка", "Граф не сгенерирован.");
        return;
    }

    int start = startDfsSpin->value();
    int end = endDfsSpin->value();

    if (start > graphs[activeGraphIndex]->getAdjacency().getRows() || end > graphs[activeGraphIndex]->getAdjacency().getRows()) {
        QMessageBox::warning(this, "Ошибка", "Номера вершин больше количества вершин графа.");
        return;
    }

    if(!(graphs[activeGraphIndex]->checkEdge(start-1,end-1))){
        QMessageBox::warning(this, "Ошибка", "Заданного ребра не существует.");
        return;
    }

    QString result = graphs[activeGraphIndex]->edgesDFS(start-1,end-1);

    QMessageBox::information(this, "Результат обхода графа", result);
}

void GraphApp::dijkstraAlgorithm()
{
    if(activeGraphIndex==-1){
        QMessageBox::warning(this, "Ошибка", "Граф не сгенерирован.");
        return;
    }

    if((graphs[activeGraphIndex]->getNegativeWeights()) && (!negativedijkstraCheckBox->isChecked())){
        QMessageBox::warning(this, "Ошибка", "В графе могут присутствовать отрицательные веса!\n"
                                             "Используйте алгоритм Дейкстры для отрицательных весов "
                                             "или сгенерируйте новый граф.");
        return;
    }

    QVector<int> distances;

    if(negativedijkstraCheckBox->isChecked()){
        auto result =  graphs[activeGraphIndex]->dijkstraWithNeg(dijkstraSpin->value()-1,dijkstraWithNegIterations);
        distances = result.first;
        dijkstraPaths = result.second;
    } else {
        auto result =  graphs[activeGraphIndex]->dijkstra(dijkstraSpin->value()-1,dijkstraIterations);
        distances = result.first;
        dijkstraPaths = result.second;
    }

    changeInfo();

    dijkstraTable->setRowCount(distances.size());
    dijkstraTable->setColumnCount(2);

    dijkstraTable->setHorizontalHeaderLabels({"Вершина", "Расстояние"});

    for (int i = 0; i < distances.size(); ++i) {
        QTableWidgetItem* vertexItem = new QTableWidgetItem(QString::number(i+1));
        dijkstraTable->setItem(i, 0, vertexItem);


        int dist = distances[i];
        QString distStr;

        if(dist == INT_MAX){
            distStr = "\u221E";
        } else{
            distStr = QString::number(dist);
        }

        QTableWidgetItem* distanceItem = new QTableWidgetItem(distStr);
        dijkstraTable->setItem(i, 1, distanceItem);
    }

    dijkstraTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    dijkstraTable->setSelectionMode(QAbstractItemView::NoSelection);
}

void GraphApp::onDijkstraTableClicked(QTableWidgetItem *item) {
    int row = item->row();
    int vertex = dijkstraTable->item(row, 0)->text().toInt()-1;

    if(dijkstraPaths.empty()) return;

    QVector<int> path = dijkstraPaths[vertex];

    if(path.empty()) return;

    view->highlightPath(path);
}


// ДЕЛЕГАТ ДЛЯ ТАБЛИЦ -------------------------------------------------------------------------------

HighlightNonEmptyDelegate::HighlightNonEmptyDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void HighlightNonEmptyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QVariant data = index.data(Qt::DisplayRole);

    if (data.toInt()!=0)
    {
        QStyleOptionViewItem opt = option;
        initStyleOption(&opt, index);

        painter->fillRect(opt.rect, QColor(8, 14, 82));

        painter->setPen(opt.palette.color(QPalette::Text));
        painter->drawText(opt.rect, opt.displayAlignment, data.toString());
    }
    else
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

// ДЕЛЕГАТ ДЛЯ ТАБЛИЦ -------------------------------------------------------------------------------



// ДИАЛОГ ДЛЯ ПУТЕЙ ---------------------------------------------------------------------------------

PathsDialog::PathsDialog(const QVector<QVector<int> > &paths, QWidget *parent)
    : paths(paths) ,QDialog(parent) {
    setWindowTitle("Маршруты между вершинами");
    setMinimumSize(300, 200);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Возможные маршруты:", this);
    layout->addWidget(label);

    listWidget = new QListWidget(this);
    for (const QVector<int>& path : paths) {
        QString pathString = "Маршрут: " + QString::fromStdString(formatPath(path));
        listWidget->addItem(pathString);
    }
    layout->addWidget(listWidget);

    connect(listWidget, &QListWidget::itemClicked, this, &PathsDialog::emitPathSelected);
}

std::string PathsDialog::formatPath(const QVector<int> &path) {
    std::stringstream ss;
    for (int i = 0; i < path.size(); ++i) {
        ss << (path[i] + 1);
        if (i < path.size() - 1) {
            ss << " -> ";
        }
    }
    return ss.str();
}

void PathsDialog::emitPathSelected(QListWidgetItem *item) {
    int index = listWidget->row(item);
    emit pathSelected(paths[index]);
}

// ДИАЛОГ ДЛЯ ПУТЕЙ ---------------------------------------------------------------------------------
