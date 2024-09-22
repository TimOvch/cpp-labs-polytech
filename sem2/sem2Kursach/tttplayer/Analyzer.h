#pragma once
#include "player.h"
#include <map>

namespace ovchinnikov_2 {
// Шорткаты:
#define is_in_bound(a) (game.get_state().field->get_current_boundary().is_within(a))
#define get_val(a) (game.get_state().field->get_value(a))
#define min_p (game.get_state().field->get_current_boundary().min)
#define max_p (game.get_state().field->get_current_boundary().max)
#define is_not_edge(a, b) (((is_in_bound(a)) && (get_val(next) != Mark::None) || (!is_in_bound(a))) && ((is_in_bound(b)) && (get_val(b) != Mark::None) || (!is_in_bound(b))))
#define is_opp_or_edge(a, b) ((is_in_bound(a) && (get_val(a)) == opp_mark(b)))
#define is_same_mark(a, b) (is_in_bound(a) && (get_val(a) == b))

//Константы подсчёта:
#define beta 0.2
#define basic_price 10
#define CENTER_PRICE_CONSTANT 2000

// Перечисление возможных направлений, по которым можно собрать комбинацию
    enum Line {
        Horizontal,
        ThirdToFirst,
        Vertical,
        SecondToFourth,
        Last
    };

// Перечисление для деления цены на атакующую и защищающуюся
    enum Status {
        Defence,
        Attack
    };

// Перечисление типов комбинаций
    enum Combination {
        Full,
        Half
    };

// Класс необходимый для хранения цены пустой ячейки / для пометки использованных ячеек с символами
    class PointData {
        double def_price;
        double att_price;
        bool used_lines[(int) Last];
        Mark mark;
    public:
        PointData();

        [[nodiscard]] double get_price() const;

        [[nodiscard]] Status get_status() const;

        // Проверка был ли уже использован символ в конкретном направлении
        bool is_line_used(const Line &line);

        // Добавление цены
        void add_price(const double &price, const Status &status);

        // Метка использованного символа
        void marked(const Mark &incomeMark, const Line &line);
    };

// Структура необходимая для работы map (сравнивает точки)
    struct comp {
        bool operator()(const Point &point, const Point &p2) const;
    };

// Класс необходимый для удобного хранения информации о точках с доступом по точке
    class PointDataContainer {
        std::map<Point, PointData, comp> data;
        Point max_price_point;
        double max_price;
        Status max_price_status;
    public:
        PointDataContainer();

        [[nodiscard]] Point get_max_point() const;

        [[nodiscard]] Status get_max_status() const;

        // Добавление цены по точке
        void add_price(const Point &point, const double &price, const Status &status);

        // Метка использованного символа по точке
        void marked(const Point &point, const Mark &mark, const Line &line);

        // Проверка на использование в направлении по точке
        bool is_line_used(const Point &point, const Line &line);
    };

// Структура необходимая для подсчёта цены точки по информации о ней
    struct PointPriceInfo {
        const Point &point;
        const short power;
        const Combination &combination;
        const short distance;
        const bool between;
    };

//Вспомогательный класс для передачи состояния в метод get_sells_and_prices
    struct SellAndPricesInfo {
        const short &power;

        Point (*dir)(const Point &, const Line &);

        const Mark &pointMark;
        Point &directionPoint;
        const Line &line;
        const Combination &combination;
    };

// Основной класс необходимый для работы с моим методом подсчёта
    class Analyzer {
        PointDataContainer container;
        Status prevStatus;
        Mark myMark;
        double alpha;

        // Подсчёт цен комбинаций вокруг ячейки с символом по всем направлениям
        void lines_checker(const GameView &game, const Point &main, const Mark &pmark);

        void get_sells_and_prices(const GameView &game, SellAndPricesInfo &info);

    public:
        Analyzer(const Status &prevStarus, const Mark &myMark, const double &alpha);

        // Подсчёт всех цен для игрового состояния
        void analyze(const GameView &game);

        // Получение точки ячейки с максимальной ценой
        [[nodiscard]] Point decision() const;

        // Получение статуса ячейки с максимальной ценой
        [[nodiscard]] Status next_prev_status() const;
    };

// Функции, используюемые в процессе анализа:

// Следующая точка в положительную сторону по направлению
    Point line_inc(const Point &point, const Line &line);

// Следующая точка в отрицательную сторону по направлению
    Point line_dec(const Point &point, const Line &line);

// Получение обратного символа
    Mark opp_mark(const Mark &mark);

// Получение уникального числа по точке
    int point_to_int(const Point &point);

// Подсчёт цены по информации о точке, константы подсчёта, статуса предыдущего хода и статуса ячейки
    double count_price(const PointPriceInfo &pointInfo, const double &alpha, const Status &prevStatus,
                       const Status &pointStatus);

// Получение статуса точки по моему символу и символу точки
    Status mark_to_status(const Mark &myMark, const Mark &other);

/*
 *  Проверка комбинации на закрытость по игровой ситуации,
 *  следующей и предыдущей точки, линии и символа в проверяемой ячейке
 */
    bool combination_is_closed(const GameView &game, Point nextPoint, Point prevPoint, const Line &line,
                               const Mark &pointMark);
}