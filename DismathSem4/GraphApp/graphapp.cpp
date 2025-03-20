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
    tabWidget->setMinimumSize(600, 500);
    adjacencyTable = new QTableWidget();
    shimbellTable = new QTableWidget();
    weightsTable = new QTableWidget();
    tabWidget->addTab(adjacencyTable, "Матрица смежности");
    tabWidget->addTab(weightsTable, "Матрица весов");
    tabWidget->addTab(shimbellTable, "Метод Шимбелла");
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
    verticesSpin->setRange(2, 50);
    verticesAction->setDefaultWidget(verticesSpin);
    graphControlMenu->addAction(verticesAction);

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

    // ПОИСК ПУТЕЙ
    QToolButton *pathControlButton = new QToolButton(toolBar);
    pathControlButton->setText("Поиск путей");
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
}

void GraphApp::generateGraph()
{
    graphsCount++;
    if(graphTypeCombo->currentIndex() == 0){
        AbstractGraph* newGraph = new OrientedGraph(verticesSpin->value());
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
    view->setAdjacencyMatrix((graphs[activeGraphIndex])->getWeights().getData(),1);
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
                newGraph = new OrientedGraph(verticesCount);
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
    graphInfoDisplay->setText(QString("Количество путей из %1 в %2: %3").arg(start).arg(end).arg(result.first));
}



