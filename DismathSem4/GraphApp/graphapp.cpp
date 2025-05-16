#include "graphapp.h"
#include <algorithm>

GraphApp::GraphApp(QWidget *parent) : QMainWindow(parent), activeGraphIndex(-1), graphsCount(0),maxCapacity(0),minCostFlow(0),minCostFlowCost(0), spanTreesNum(0) {
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

    QTabWidget *tabWidget = new QTabWidget();
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
    capacityTable = new QTableWidget();
    capacityTable->setItemDelegate(delegate);
    capacityTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    costsTable = new QTableWidget();
    costsTable->setItemDelegate(delegate);
    costsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    kirchgoff = new QTableWidget();
    kirchgoff->setItemDelegate(delegate);
    kirchgoff->setEditTriggers(QAbstractItemView::NoEditTriggers);
    takenCapabilityTable = new QTableWidget();
    takenCapabilityTable->setItemDelegate(delegate);
    takenCapabilityTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    dijkstraTable = new QTableWidget();
    dijkstraTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(dijkstraTable, &QTableWidget::itemClicked, this, &GraphApp::onDijkstraTableClicked);
    tabWidget->addTab(adjacencyTable, "Смежность");
    tabWidget->addTab(weightsTable, "Веса");
    tabWidget->addTab(capacityTable, "Потоки");
    tabWidget->addTab(costsTable, "Стоимости");
    tabWidget->addTab(kirchgoff, "Кирхгофа");
    tabWidget->addTab(takenCapabilityTable, "Пущ. потоки");
    tabWidget->addTab(shimbellTable, "Шимбелла");
    tabWidget->addTab(dijkstraTable, "Дейкстры");
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
    graphTypeCombo->addItems({"Ориентированный","Неориентированный"});
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


    //НАСТРОЙКА ВИЗУАЛИЗАЦИИ
    QToolButton *viewButton = new QToolButton(toolBar);
    viewButton->setText("Визуализация");
    QMenu *viewMenu = new QMenu(viewButton);
    viewMenu->setStyleSheet(
        "QMenu { padding: 10px; }"
        "QMenu::item { padding: 10px 10px; }"
        );

    QWidgetAction *showWeightsAction = new QWidgetAction(viewMenu);
    showWeightsCheckBox = new QCheckBox("Отображение весов", this);
    showWeightsCheckBox->setChecked(true);
    connect(showWeightsCheckBox, &QCheckBox::checkStateChanged, this, &GraphApp::changeView);
    showWeightsAction->setDefaultWidget(showWeightsCheckBox);
    viewMenu->addAction(showWeightsAction);

    QWidgetAction *showCapsAction = new QWidgetAction(viewMenu);
    showCapacitiesCheckBox = new QCheckBox("Отображение пропускных способностей", this);
    showCapacitiesCheckBox->setChecked(true);
    connect(showCapacitiesCheckBox, &QCheckBox::checkStateChanged, this, &GraphApp::changeView);
    showCapsAction->setDefaultWidget(showCapacitiesCheckBox);
    viewMenu->addAction(showCapsAction);

    QWidgetAction *showCostsAction = new QWidgetAction(viewMenu);
    showCostsCheckBox = new QCheckBox("Отображение стоимостей", this);
    showCostsCheckBox->setChecked(true);
    connect(showCostsCheckBox, &QCheckBox::checkStateChanged, this, &GraphApp::changeView);
    showCostsAction->setDefaultWidget(showCostsCheckBox);
    viewMenu->addAction(showCostsAction);

    QWidgetAction *showSetsAction = new QWidgetAction(viewMenu);
    showSetsCheckBox = new QCheckBox("Отображение макс. независимых множеств ребер", this);
    showSetsCheckBox->setChecked(false);
    connect(showSetsCheckBox, &QCheckBox::checkStateChanged, this, &GraphApp::setsChanges);
    showSetsAction->setDefaultWidget(showSetsCheckBox);
    viewMenu->addAction(showSetsAction);

    QWidgetAction *showTreeAction = new QWidgetAction(viewMenu);
    showCombo = new QComboBox(this);
    showCombo->addItem("Граф");
    showCombo->addItem("Остов");
    connect(showCombo, &QComboBox::currentIndexChanged, this, &GraphApp::changeTypeView);
    showTreeAction->setDefaultWidget(showCombo);
    viewMenu->addAction(showTreeAction);

    viewButton->setMenu(viewMenu);
    viewButton->setPopupMode(QToolButton::InstantPopup);
    toolBar->addWidget(viewButton);



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
    // QToolButton *fileControlButton = new QToolButton(toolBar);
    // fileControlButton->setText("Файл");
    // QMenu *fileControlMenu = new QMenu(fileControlButton);
    // fileControlMenu->setStyleSheet(
    //     "QMenu { padding: 10px; }"
    //     "QMenu::item { padding: 10px 10px; }"
    //     );

    // QAction *openAction = new QAction("Открыть из файла", fileControlMenu);
    // connect(openAction, &QAction::triggered, app, &GraphApp::loadGraphFromFile);
    // fileControlMenu->addAction(openAction);

    // QAction *saveAction = new QAction("Сохранить в файл", fileControlMenu);
    // connect(saveAction, &QAction::triggered, app, &GraphApp::saveGraphToFile);
    // fileControlMenu->addAction(saveAction);

    // fileControlButton->setMenu(fileControlMenu);
    // fileControlButton->setPopupMode(QToolButton::InstantPopup);
    // toolBar->addWidget(fileControlButton);


    // КОЛ-ВО ОСТОВОВ
    QToolButton *spanNumButton = new QToolButton(toolBar);
    spanNumButton->setText("Остовы");
    QMenu *spanNumMenu = new QMenu(spanNumButton);
    spanNumMenu->setStyleSheet(
        "QMenu { padding: 10px; }"
        "QMenu::item { padding: 10px 10px; }"
        );

    QWidgetAction *spanGetAction = new QWidgetAction(spanNumMenu);
    QPushButton *spanBut = new QPushButton("Вычислить кол-во остов", this);
    connect(spanBut,&QPushButton::clicked, this, &GraphApp::spanNum);
    spanGetAction->setDefaultWidget(spanBut);
    spanNumMenu->addAction(spanGetAction);

    QWidgetAction *pruferWidgetAction = new QWidgetAction(spanNumMenu);
    QPushButton *pruferWidgetBut = new QPushButton("Отобразить дерево по коду Прюфера", this);
    connect(pruferWidgetBut,&QPushButton::clicked, this, &GraphApp::openPruferWidget);
    pruferWidgetAction->setDefaultWidget(pruferWidgetBut);
    spanNumMenu->addAction(pruferWidgetAction);

    spanNumButton->setMenu(spanNumMenu);
    spanNumButton->setPopupMode(QToolButton::InstantPopup);
    toolBar->addWidget(spanNumButton);


    // ЭЙЛЕРОВ И ГАМИЛЬТОНОВ
    QToolButton *cycleButton = new QToolButton(toolBar);
    cycleButton->setText("Циклы");
    QMenu *cycleMenu = new QMenu(cycleButton);
    cycleMenu->setStyleSheet(
        "QMenu { padding: 10px; }"
        "QMenu::item { padding: 10px 10px; }"
        );

    QWidgetAction *eulerAction = new QWidgetAction(cycleMenu);
    QPushButton *eulerBut = new QPushButton("Дополнить до Эйлерова", this);
    connect(eulerBut,&QPushButton::clicked, this, &GraphApp::makeEuler);
    eulerAction->setDefaultWidget(eulerBut);
    cycleMenu->addAction(eulerAction);

    QWidgetAction *gamiltonAction = new QWidgetAction(cycleMenu);
    QPushButton *gamiltonBut = new QPushButton("Дополнить до Гамильтонова", this);
    connect(gamiltonBut,&QPushButton::clicked, this, &GraphApp::makeHamilton);
    gamiltonAction->setDefaultWidget(gamiltonBut);
    cycleMenu->addAction(gamiltonAction);

    QWidgetAction *gamiltonShowAction = new QWidgetAction(cycleMenu);
    QPushButton *gamiltonShowBut = new QPushButton("Показать Гамильтоновы циклы", this);
    connect(gamiltonShowBut,&QPushButton::clicked, this, &GraphApp::showHamCycle);
    gamiltonShowAction->setDefaultWidget(gamiltonShowBut);
    cycleMenu->addAction(gamiltonShowAction);

    QWidgetAction *eulerShowAction = new QWidgetAction(cycleMenu);
    showCycleEdgesBox = new QCheckBox("Отображение дополненных ребер");
    connect(showCycleEdgesBox,&QCheckBox::toggled, this, &GraphApp::showCycleEdges);
    eulerShowAction->setDefaultWidget(showCycleEdgesBox);
    cycleMenu->addAction(eulerShowAction);

    QWidgetAction *loadAction = new QWidgetAction(cycleMenu);
    QPushButton *loadBut = new QPushButton("Вернуть исходный граф", this);
    connect(loadBut,&QPushButton::clicked, this, &GraphApp::loadGraph);
    loadAction->setDefaultWidget(loadBut);
    cycleMenu->addAction(loadAction);

    cycleButton->setMenu(cycleMenu);
    cycleButton->setPopupMode(QToolButton::InstantPopup);
    toolBar->addWidget(cycleButton);
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
    AbstractGraph* newGraph = new OrientedGraph(verticesSpin->value(),negativeWeightsCheckBox->isChecked());
    newGraph->setName("Новый граф");
    newGraph->acycleGraphGenerate();
    graphs.push_back(newGraph);
    activeGraphIndex = graphs.size()-1;
    if(graphTypeCombo->currentIndex() == 1){
        newGraph->makeUnoriented();
    }
    changeActiveGraph(activeGraphIndex);
}

void GraphApp::changeActiveGraph(const int &newActiveGraphIndex)
{
    activeGraphIndex = newActiveGraphIndex;
    dijkstraIterations = 0;
    dijkstraWithNegIterations = 0;
    eulerCycle.clear();
    dijkstraTable->clear();
    bool isUnoriented = (graphs[activeGraphIndex])->getIsUnoriented();

    view->setAdjacencyMatrix((graphs[activeGraphIndex])->getAdjacency().getData(),!isUnoriented);
    view->setWeightsMatrix((graphs[activeGraphIndex])->getWeights().getData());

    if(!isUnoriented){
        QVector<QPair<int,int>> setGraph = graphs[activeGraphIndex]->maxEdgeIndependentSetDAG();
        QVector<QPair<int,int>> setTree =  graphs[activeGraphIndex]->maxIndependentEdgeSetTree();

        view->setEdgesSets(setGraph,setTree);

        auto res = (graphs[activeGraphIndex]->minCostFlow());

        maxCapacity =  graphs[activeGraphIndex]->fordFulkerson();
        minCostFlow = res.first;
        minCostFlowCost = res.second;
        minSetGraph = setGraph.size();
        minSetTree = setTree.size();

        view->setCapacitiesMatrix((graphs[activeGraphIndex])->getCapacities().getData());
        view->setCostsMatrix((graphs[activeGraphIndex])->getCosts().getData());

        changeTable(capacityTable,(graphs[activeGraphIndex])->getCapacities().getData());
        changeTable(costsTable,(graphs[activeGraphIndex])->getCosts().getData());
        changeTable(takenCapabilityTable,graphs[activeGraphIndex]->getTakenCaps().getData());
    }

    auto prf = graphs[activeGraphIndex]->getPruferStr();
    auto eul = graphs[activeGraphIndex]->isEuler();

    spanTreesNum = 0;
    primSum = graphs[activeGraphIndex]->getSum();    
    prufersCode = prf.first;
    prufersWeights = prf.second;
    (graphs[activeGraphIndex])->countKirchhoff();
    euler = eul.first;
    halfEuler = eul.second;
    qDebug() << "test1";
    hamilCycle = (graphs[activeGraphIndex])->hamiltonCyclesStr();

    if(euler){
        eulerCycle = (graphs[activeGraphIndex])->eulerCycleStr();
    } else{
        eulerCycle = "";
    }

    changeTable(adjacencyTable,(graphs[activeGraphIndex])->getAdjacency().getData());
    changeTable(shimbellTable,(graphs[activeGraphIndex])->getWeights().getData());
    changeTable(weightsTable,(graphs[activeGraphIndex])->getWeights().getData());
    changeTable(kirchgoff,(graphs[activeGraphIndex])->getKirchhoff().getData());

    refactorSpinBoxes();
    changeInfo();

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

void GraphApp::changeView()
{
    view->setParametrs(showWeightsCheckBox->isChecked(),showCapacitiesCheckBox->isChecked(),showCostsCheckBox->isChecked());
}

void GraphApp::changeTypeView(int index)
{
    if(index == 0){
        view->setAdjacencyMatrix((graphs[activeGraphIndex])->getAdjacency().getData(),!(graphs[activeGraphIndex])->getIsUnoriented());
        view->setWeightsMatrix((graphs[activeGraphIndex])->getWeights().getData());
        if(!graphs[activeGraphIndex]->getIsUnoriented()){
            view->setCapacitiesMatrix((graphs[activeGraphIndex])->getCapacities().getData());
            view->setCostsMatrix((graphs[activeGraphIndex])->getCosts().getData());
        }
    } else{
        QPair<QVector<int>,QVector<int>> prufer = graphs[activeGraphIndex]->getPrufer();
        view->setTreeFromPrufer(prufer.first,prufer.second);
    }
}

void GraphApp::changeInfo()
{
    AbstractGraph* activeGraph = graphs[activeGraphIndex];
    QString info;

    if(!activeGraph->getIsUnoriented()){
        info = QString(
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
                   "<tr><td style='padding: 5px; width: 40%;'><b>Максимальный поток:</b></td><td style='padding: 5px;'>%9</td></tr>"
                   "<tr><td style='padding: 5px; width: 40%;'><b>Поток (%10) минимальной стоимости:</b></td><td style='padding: 5px;'>%11</td></tr>"
                   "<tr><td style='padding: 5px; width: 40%;'><b>Кол-во остовных деревьев:</b></td><td style='padding: 5px;'>%12</td></tr>"
                   "<tr><td style='padding: 5px; width: 40%;'><b>Суммарный вес остова:</b></td><td style='padding: 5px;'>%13</td></tr>"
                   "<tr><td style='padding: 5px; width: 40%;'><b>Мощность мн-ва независимых ребер (граф):</b></td><td style='padding: 5px;'>%14</td></tr>"
                   "<tr><td style='padding: 5px; width: 40%;'><b>Мощность мн-ва независимых ребер (дерево):</b></td><td style='padding: 5px;'>%15</td></tr>"
                   "<tr><td style='padding: 5px; width: 40%;'><b>Код Прюфера для остова:</b></td><td style='padding: 5px;'>%16</td></tr>"
                   "<tr><td style='padding: 5px; width: 40%;'><b>Веса кода Прюфера:</b></td><td style='padding: 5px;'>%17</td></tr>"
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
                   .arg(dijkstraWithNegIterations)
                   .arg(maxCapacity)
                   .arg(minCostFlow)
                   .arg(minCostFlowCost)
                   .arg(spanTreesNum)
                   .arg(primSum)
                   .arg(minSetGraph)
                   .arg(minSetTree)
                   .arg(prufersCode)
                   .arg(prufersWeights);
    } else{
        info = QString(
                   "<div style='padding: 10px;'>"
                   "<h1 style='margin-bottom: 20px;'>Информация о графе</h1>"
                   "<table style='width: 100%; border-collapse: collapse;'>"
                   "<tr><td style='padding: 5px; width: 40%;'><b>Количество вершин:</b></td><td style='padding: 5px;'>%1</td></tr>"
                   "<tr><td style='padding: 5px; width: 40%;'><b>Количество ребер:</b></td><td style='padding: 5px;'>%2</td></tr>"
                   "<tr><td style='padding: 5px; width: 40%;'><b>Тип графа:</b></td><td style='padding: 5px;'>%3</td></tr>"
                   "<tr><td style='padding: 5px; width: 40%;'><b>Связный:</b></td><td style='padding: 5px;'>%4</td></tr>"
                   "<tr><td style='padding: 5px; width: 40%;'><b>Отрицательные веса:</b></td><td style='padding: 5px;'>%5</td></tr>"
                   "<tr><td style='padding: 5px; width: 40%;'><b>Итерации Дейкстры:</b></td><td style='padding: 5px;'>%6</td></tr>"
                   "<tr><td style='padding: 5px; width: 40%;'><b>Итерации Дейкстры с отр. весами:</b></td><td style='padding: 5px;'>%7</td></tr>"
                   "<tr><td style='padding: 5px; width: 40%;'><b>Кол-во остовных деревьев:</b></td><td style='padding: 5px;'>%8</td></tr>"
                   "<tr><td style='padding: 5px; width: 40%;'><b>Суммарный вес остова:</b></td><td style='padding: 5px;'>%9</td></tr>"
                   "<tr><td style='padding: 5px; width: 40%;'><b>Код Прюфера для остова:</b></td><td style='padding: 5px;'>%10</td></tr>"
                   "<tr><td style='padding: 5px; width: 40%;'><b>Веса кода Прюфера:</b></td><td style='padding: 5px;'>%11</td></tr>"
                   "<tr><td style='padding: 5px; width: 40%;'><b>Эйлеров:</b></td><td style='padding: 5px;'>%12</td></tr>"
                   "<tr><td style='padding: 5px; width: 40%;'><b>Эйлеров цикл:</b></td><td style='padding: 5px;'>%13</td></tr>"
                   "<tr><td style='padding: 5px; width: 40%;'><b>Гамильтонов:</b></td><td style='padding: 5px;'>%14</td></tr>"
                   "</table>"
                   "</div>"
                   )
                   .arg(activeGraph->getP())
                   .arg(activeGraph->getQ())
                   .arg(activeGraph->getType())
                   .arg(activeGraph->getConnected() ? "Да" : "Нет")
                   .arg(activeGraph->getNegativeWeights() ? "Да" : "Нет")
                   .arg(dijkstraIterations)
                   .arg(dijkstraWithNegIterations)
                   .arg(spanTreesNum)
                   .arg(primSum)
                   .arg(prufersCode)
                   .arg(prufersWeights)
                   .arg(euler ? "Да" : "Нет")
                   .arg(eulerCycle)
                   .arg(hamilCycle);
    }

    graphInfoDisplay->setText(info);
}

void GraphApp::tabChanged(int index)
{
    view->clearHighlightedPath();
}

void GraphApp::setsChanges()
{
    view->setEdgesHighlight(showSetsCheckBox->isChecked());
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

void GraphApp::spanNum()
{
    spanTreesNum = graphs[activeGraphIndex]->getSpanTreesNum();
    changeInfo();
}

void GraphApp::openPruferWidget()
{
    PruferWidget *wid = new PruferWidget(this);
    wid->show();
}

void GraphApp::makeEuler()
{
    if(euler || !((graphs[activeGraphIndex])->getIsUnoriented())){
        return;
    }

    bool possible;
    auto dop = (graphs[activeGraphIndex])->makeEuler(possible);

    if(!possible){
        QMessageBox::warning(this,"Ошибка", "Граф невозможно привести к Эйлерову!");
        return;
    }

    view->setCycleEdgesHighlight(1);
    showCycleEdgesBox->setChecked(1);

    view->setAdjacencyMatrix((graphs[activeGraphIndex])->getAdjacency().getData(),0);
    view->setWeightsMatrix((graphs[activeGraphIndex])->getWeights().getData());

    auto prf = graphs[activeGraphIndex]->getPruferStr();
    auto eul = graphs[activeGraphIndex]->isEuler();

    spanTreesNum = 0;
    primSum = graphs[activeGraphIndex]->getSum();
    prufersCode = prf.first;
    prufersWeights = prf.second;
    (graphs[activeGraphIndex])->countKirchhoff();
    euler = eul.first;
    halfEuler = eul.second;
    if(euler){
        eulerCycle = (graphs[activeGraphIndex])->eulerCycleStr();
    } else{
        eulerCycle = "";
    }
    hamilCycle = (graphs[activeGraphIndex])->hamiltonCyclesStr();

    changeTable(adjacencyTable,(graphs[activeGraphIndex])->getAdjacency().getData());
    changeTable(shimbellTable,(graphs[activeGraphIndex])->getWeights().getData());
    changeTable(weightsTable,(graphs[activeGraphIndex])->getWeights().getData());
    changeTable(kirchgoff,(graphs[activeGraphIndex])->getKirchhoff().getData());

    refactorSpinBoxes();
    changeInfo();

    view->highlightEdges(dop);
}

void GraphApp::makeHamilton()
{
    if(!((graphs[activeGraphIndex])->getIsUnoriented())){
        return;
    }

    if(hamilCycle == "Да"){
        return;
    }

    auto dop = (graphs[activeGraphIndex])->makeHamilton();

    view->setCycleEdgesHighlight(1);
    showCycleEdgesBox->setChecked(1);

    view->setAdjacencyMatrix((graphs[activeGraphIndex])->getAdjacency().getData(),0);
    view->setWeightsMatrix((graphs[activeGraphIndex])->getWeights().getData());

    auto prf = graphs[activeGraphIndex]->getPruferStr();
    auto eul = graphs[activeGraphIndex]->isEuler();

    spanTreesNum = 0;
    primSum = graphs[activeGraphIndex]->getSum();
    prufersCode = prf.first;
    prufersWeights = prf.second;
    (graphs[activeGraphIndex])->countKirchhoff();
    euler = eul.first;
    halfEuler = eul.second;
    hamilCycle = (graphs[activeGraphIndex])->hamiltonCyclesStr();

    if(euler){
        eulerCycle = (graphs[activeGraphIndex])->eulerCycleStr();
    } else{
        eulerCycle = "";
    }

    changeTable(adjacencyTable,(graphs[activeGraphIndex])->getAdjacency().getData());
    changeTable(shimbellTable,(graphs[activeGraphIndex])->getWeights().getData());
    changeTable(weightsTable,(graphs[activeGraphIndex])->getWeights().getData());
    changeTable(kirchgoff,(graphs[activeGraphIndex])->getKirchhoff().getData());

    refactorSpinBoxes();
    changeInfo();

    view->highlightEdges(qMakePair(dop,QVector<QPair<int,int>>(0)));
}

void GraphApp::showHamCycle()
{
    auto res = (graphs[activeGraphIndex])->findHamiltonianCycles();

    QVector<int> weights(res.size());
    QVector<QVector<int>> paths(res.size());

    for(int i = 0; i < res.size(); i++){
        weights[i] = res[i].second;
        paths[i] = res[i].first;
    }

    PathsDialog *dialog = new PathsDialog(paths, this,weights);
    connect(dialog, &PathsDialog::pathSelected, this, &GraphApp::handlePathSelected);
    dialog->exec();
    view->clearHighlightedPath();
}

void GraphApp::showCycleEdges(bool high)
{
    view->setCycleEdgesHighlight(high);
}

void GraphApp::loadGraph()
{
    (graphs[activeGraphIndex])->load();

    dijkstraIterations = 0;
    dijkstraWithNegIterations = 0;
    eulerCycle.clear();
    dijkstraTable->clear();
    bool isUnoriented = (graphs[activeGraphIndex])->getIsUnoriented();

    view->setAdjacencyMatrix((graphs[activeGraphIndex])->getAdjacency().getData(),!isUnoriented);
    view->setWeightsMatrix((graphs[activeGraphIndex])->getWeights().getData());

    if(!isUnoriented){
        QVector<QPair<int,int>> setGraph = graphs[activeGraphIndex]->maxEdgeIndependentSetDAG();
        QVector<QPair<int,int>> setTree =  graphs[activeGraphIndex]->maxIndependentEdgeSetTree();

        view->setEdgesSets(setGraph,setTree);

        auto res = (graphs[activeGraphIndex]->minCostFlow());

        maxCapacity =  graphs[activeGraphIndex]->fordFulkerson();
        minCostFlow = res.first;
        minCostFlowCost = res.second;
        minSetGraph = setGraph.size();
        minSetTree = setTree.size();

        view->setCapacitiesMatrix((graphs[activeGraphIndex])->getCapacities().getData());
        view->setCostsMatrix((graphs[activeGraphIndex])->getCosts().getData());

        changeTable(capacityTable,(graphs[activeGraphIndex])->getCapacities().getData());
        changeTable(costsTable,(graphs[activeGraphIndex])->getCosts().getData());
        changeTable(takenCapabilityTable,graphs[activeGraphIndex]->getTakenCaps().getData());
    }

    auto prf = graphs[activeGraphIndex]->getPruferStr();
    auto eul = graphs[activeGraphIndex]->isEuler();

    spanTreesNum = 0;
    primSum = graphs[activeGraphIndex]->getSum();
    prufersCode = prf.first;
    prufersWeights = prf.second;
    (graphs[activeGraphIndex])->countKirchhoff();
    euler = eul.first;
    halfEuler = eul.second;
    hamilCycle = (graphs[activeGraphIndex])->hamiltonCyclesStr();

    if(euler){
        eulerCycle = (graphs[activeGraphIndex])->eulerCycleStr();
    } else{
        eulerCycle = "";
    }

    changeTable(adjacencyTable,(graphs[activeGraphIndex])->getAdjacency().getData());
    changeTable(shimbellTable,(graphs[activeGraphIndex])->getWeights().getData());
    changeTable(weightsTable,(graphs[activeGraphIndex])->getWeights().getData());
    changeTable(kirchgoff,(graphs[activeGraphIndex])->getKirchhoff().getData());

    refactorSpinBoxes();
    changeInfo();
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

void sortWithReference(QVector<QVector<int>> &refArray, QVector<int> &sortArray) {
    QVector<int> indices(sortArray.size());
    for (int i = 0; i < sortArray.size(); ++i) {
        indices[i] = i;
    }

    std::sort(indices.begin(), indices.end(), [&](int a, int b) {
        return sortArray[a] < sortArray[b];
    });

    QVector<int> sortedValues(sortArray.size());
    QVector<QVector<int>> sortedRefArray(sortArray.size(), QVector<int>(refArray[0].size()));

    for (int i = 0; i < indices.size(); ++i) {
        sortedValues[i] = sortArray[indices[i]];
        sortedRefArray[i] = refArray[indices[i]];
    }

    sortArray = sortedValues;
    refArray = sortedRefArray;
}

PathsDialog::PathsDialog(const QVector<QVector<int>> &pths, QWidget *parent, QVector<int> wghts)
    : paths(pths) ,QDialog(parent), weights(wghts) {
    if(wghts.isEmpty()){
        setWindowTitle("Маршруты между вершинами");
    } else{
        setWindowTitle("Гамильтоновы циклы");
    }

    setMinimumSize(300, 200);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label;
    if(wghts.isEmpty()){
        label = new QLabel("Возможные маршруты:", this);
    } else {
        label = new QLabel("Гамильтоновы циклы и веса:", this);
    }
    layout->addWidget(label);

    if(!wghts.isEmpty()){
        sortWithReference(paths,weights);
    }

    listWidget = new QListWidget(this);
    for (int i = 0; i < paths.size(); i++) {
        QString pathString;
        if(i == 0){
            pathString = (wghts.isEmpty() ? "Маршрут: " : "(Решение задачи коммивояжера) Цикл: ") + QString::fromStdString(formatPath(paths[i]));
        } else{ // (Решение задачи коммивояжера)
            pathString = (wghts.isEmpty() ? "Маршрут: " : "Цикл: ") + QString::fromStdString(formatPath(paths[i]));
        }
        if(!wghts.isEmpty()){
            pathString += " Вес: " + QString::number(weights[i]);
        }
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
