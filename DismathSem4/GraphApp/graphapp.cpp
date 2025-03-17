#include "graphapp.h"

GraphApp::GraphApp(QWidget *parent) : QMainWindow(parent), activeGraphIndex(-1), graphsCount(0) {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *upperLayout = new QHBoxLayout();
    QHBoxLayout *lowerLayout = new QHBoxLayout();

    view = new GraphView(this);
    view->setMinimumSize(600, 400);
    upperLayout->addWidget(view);

    QTabWidget *tabWidget = new QTabWidget;
    tabWidget->setMinimumSize(400,400);
    tabWidget->show();
    adjacencyTable = new QTableWidget();
    shimbellTable = new QTableWidget();
    tabWidget->addTab(adjacencyTable, "Матрица смежности");
    tabWidget->addTab(shimbellTable, "Метод Шимбелла");

    upperLayout->addWidget(tabWidget);

    mainLayout->addLayout(upperLayout);

    graphInfoDisplay = new QTextEdit(this);
    graphInfoDisplay->setReadOnly(true);
    lowerLayout->addWidget(graphInfoDisplay);

    QVBoxLayout *controlsLayout1 = new QVBoxLayout();
    controlsLayout1->setAlignment(Qt::AlignTop);

    graphTypeCombo = new QComboBox(this);
    graphTypeCombo->addItems({"Ориентированный"});
    controlsLayout1->addWidget(graphTypeCombo);

    verticesSpin = new QSpinBox(this);
    verticesSpin->setRange(2, 50);
    controlsLayout1->addWidget(verticesSpin);

    QPushButton *generateBtn = new QPushButton("Генерировать", this);
    controlsLayout1->addWidget(generateBtn);
    connect(generateBtn,&QPushButton::clicked,this,&GraphApp::generateGraph);

    lowerLayout->addLayout(controlsLayout1);

    QVBoxLayout *controlsLayout2 = new QVBoxLayout();
    controlsLayout2->setAlignment(Qt::AlignTop);

    shimbellCombo = new QComboBox(this);
    shimbellCombo->addItems({"Min", "Max"});
    controlsLayout2->addWidget(shimbellCombo);

    shimbellSpin = new QSpinBox(this);
    shimbellSpin->setRange(1,100);
    controlsLayout2->addWidget(shimbellSpin);

    QPushButton *shimbellBtn = new QPushButton("Метод Шимбелла", this);
    controlsLayout2->addWidget(shimbellBtn);
    connect(shimbellBtn,&QPushButton::clicked,this,&GraphApp::shimbellMethod);

    lowerLayout->addLayout(controlsLayout2);

    QVBoxLayout *controlsLayout3 = new QVBoxLayout();
    controlsLayout3->setAlignment(Qt::AlignTop);

    QPushButton *openBtn = new QPushButton("Открыть из файла", this);
    controlsLayout3->addWidget(openBtn);
    connect(openBtn,&QPushButton::clicked,this,&GraphApp::loadGraphFromFile);

    QPushButton *saveBtn = new QPushButton("Сохранить в файл", this);
    controlsLayout3->addWidget(saveBtn);
    connect(saveBtn,&QPushButton::clicked,this,&GraphApp::saveGraphToFile);

    lowerLayout->addLayout(controlsLayout3);

    QVBoxLayout *controlsLayout4 = new QVBoxLayout();
    controlsLayout4->setAlignment(Qt::AlignTop);

    QLabel *startLabel = new QLabel("Начальная вершина:", this);
    controlsLayout4->addWidget(startLabel);

    startVertexSpin = new QSpinBox(this);
    startVertexSpin->setRange(1, 50);
    controlsLayout4->addWidget(startVertexSpin);

    QLabel *endLabel = new QLabel("Конечная вершина:", this);
    controlsLayout4->addWidget(endLabel);

    endVertexSpin = new QSpinBox(this);
    endVertexSpin->setRange(1, 50);
    controlsLayout4->addWidget(endVertexSpin);

    QPushButton *dfsBtn = new QPushButton("Найти пути", this);
    controlsLayout4->addWidget(dfsBtn);
    connect(dfsBtn,&QPushButton::clicked,this,&GraphApp::findPaths);

    lowerLayout->addLayout(controlsLayout4);

    mainLayout->addLayout(lowerLayout);

    setCentralWidget(centralWidget);
    setWindowTitle("GraphApp");
    setFixedSize(1200,800);
}

GraphApp::~GraphApp()
{
    for (auto& graphP : graphs) {
        delete graphP;
    }
}

void GraphApp::generateGraph()
{
    if(graphsCount != 0){
        // СОХРАНИТЬ АКТИВНЫЙ ГРАФ В ФАЙЛ
    }

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
    changeAdjacencyTable((graphs[activeGraphIndex])->getAdjacency().getData());
    changeWeightsTable((graphs[activeGraphIndex])->getWeights().getData());
    view->setAdjacencyMatrix((graphs[activeGraphIndex])->getAdjacency().getData(),1);

}

void GraphApp::changeAdjacencyTable(const QVector<QVector<int> > &matrix)
{
    if (matrix.isEmpty()) {
        adjacencyTable->clear();
        return;
    }

    int rowCount = matrix.size();
    int colCount = matrix[0].size();

    adjacencyTable->setRowCount(rowCount);
    adjacencyTable->setColumnCount(colCount);

    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(matrix[row][col]));
            item->setTextAlignment(Qt::AlignCenter);
            adjacencyTable->setItem(row, col, item);
        }
    }

    adjacencyTable->resizeColumnsToContents();
    adjacencyTable->resizeRowsToContents();
}

void GraphApp::changeWeightsTable(const QVector<QVector<int> > &matrix)
{
    if (matrix.isEmpty()) {
        shimbellTable->clear();
        return;
    }

    int rowCount = matrix.size();
    int colCount = matrix[0].size();

    shimbellTable->setRowCount(rowCount);
    shimbellTable->setColumnCount(colCount);

    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(matrix[row][col]));
            item->setTextAlignment(Qt::AlignCenter);
            shimbellTable->setItem(row, col, item);
        }
    }

    shimbellTable->resizeColumnsToContents();
    shimbellTable->resizeRowsToContents();
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

    int rowCount = matrix.size();
    int colCount = matrix[0].size();

    shimbellTable->setRowCount(rowCount);
    shimbellTable->setColumnCount(colCount);

    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(matrix[row][col]));
            item->setTextAlignment(Qt::AlignCenter);
            shimbellTable->setItem(row, col, item);
        }
    }

    shimbellTable->resizeColumnsToContents();
    shimbellTable->resizeRowsToContents();
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



