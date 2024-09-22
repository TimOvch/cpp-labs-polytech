#pragma once
#include "player.h"
#include <map>

namespace ovchinnikov_2 {
// ��������:
#define is_in_bound(a) (game.get_state().field->get_current_boundary().is_within(a))
#define get_val(a) (game.get_state().field->get_value(a))
#define min_p (game.get_state().field->get_current_boundary().min)
#define max_p (game.get_state().field->get_current_boundary().max)
#define is_not_edge(a, b) (((is_in_bound(a)) && (get_val(next) != Mark::None) || (!is_in_bound(a))) && ((is_in_bound(b)) && (get_val(b) != Mark::None) || (!is_in_bound(b))))
#define is_opp_or_edge(a, b) ((is_in_bound(a) && (get_val(a)) == opp_mark(b)))
#define is_same_mark(a, b) (is_in_bound(a) && (get_val(a) == b))

//��������� ��������:
#define beta 0.2
#define basic_price 10
#define CENTER_PRICE_CONSTANT 2000

// ������������ ��������� �����������, �� ������� ����� ������� ����������
    enum Line {
        Horizontal,
        ThirdToFirst,
        Vertical,
        SecondToFourth,
        Last
    };

// ������������ ��� ������� ���� �� ��������� � ������������
    enum Status {
        Defence,
        Attack
    };

// ������������ ����� ����������
    enum Combination {
        Full,
        Half
    };

// ����� ����������� ��� �������� ���� ������ ������ / ��� ������� �������������� ����� � ���������
    class PointData {
        double def_price;
        double att_price;
        bool used_lines[(int) Last];
        Mark mark;
    public:
        PointData();

        [[nodiscard]] double get_price() const;

        [[nodiscard]] Status get_status() const;

        // �������� ��� �� ��� ����������� ������ � ���������� �����������
        bool is_line_used(const Line &line);

        // ���������� ����
        void add_price(const double &price, const Status &status);

        // ����� ��������������� �������
        void marked(const Mark &incomeMark, const Line &line);
    };

// ��������� ����������� ��� ������ map (���������� �����)
    struct comp {
        bool operator()(const Point &point, const Point &p2) const;
    };

// ����� ����������� ��� �������� �������� ���������� � ������ � �������� �� �����
    class PointDataContainer {
        std::map<Point, PointData, comp> data;
        Point max_price_point;
        double max_price;
        Status max_price_status;
    public:
        PointDataContainer();

        [[nodiscard]] Point get_max_point() const;

        [[nodiscard]] Status get_max_status() const;

        // ���������� ���� �� �����
        void add_price(const Point &point, const double &price, const Status &status);

        // ����� ��������������� ������� �� �����
        void marked(const Point &point, const Mark &mark, const Line &line);

        // �������� �� ������������� � ����������� �� �����
        bool is_line_used(const Point &point, const Line &line);
    };

// ��������� ����������� ��� �������� ���� ����� �� ���������� � ���
    struct PointPriceInfo {
        const Point &point;
        const short power;
        const Combination &combination;
        const short distance;
        const bool between;
    };

//��������������� ����� ��� �������� ��������� � ����� get_sells_and_prices
    struct SellAndPricesInfo {
        const short &power;

        Point (*dir)(const Point &, const Line &);

        const Mark &pointMark;
        Point &directionPoint;
        const Line &line;
        const Combination &combination;
    };

// �������� ����� ����������� ��� ������ � ���� ������� ��������
    class Analyzer {
        PointDataContainer container;
        Status prevStatus;
        Mark myMark;
        double alpha;

        // ������� ��� ���������� ������ ������ � �������� �� ���� ������������
        void lines_checker(const GameView &game, const Point &main, const Mark &pmark);

        void get_sells_and_prices(const GameView &game, SellAndPricesInfo &info);

    public:
        Analyzer(const Status &prevStarus, const Mark &myMark, const double &alpha);

        // ������� ���� ��� ��� �������� ���������
        void analyze(const GameView &game);

        // ��������� ����� ������ � ������������ �����
        [[nodiscard]] Point decision() const;

        // ��������� ������� ������ � ������������ �����
        [[nodiscard]] Status next_prev_status() const;
    };

// �������, ������������� � �������� �������:

// ��������� ����� � ������������� ������� �� �����������
    Point line_inc(const Point &point, const Line &line);

// ��������� ����� � ������������� ������� �� �����������
    Point line_dec(const Point &point, const Line &line);

// ��������� ��������� �������
    Mark opp_mark(const Mark &mark);

// ��������� ����������� ����� �� �����
    int point_to_int(const Point &point);

// ������� ���� �� ���������� � �����, ��������� ��������, ������� ����������� ���� � ������� ������
    double count_price(const PointPriceInfo &pointInfo, const double &alpha, const Status &prevStatus,
                       const Status &pointStatus);

// ��������� ������� ����� �� ����� ������� � ������� �����
    Status mark_to_status(const Mark &myMark, const Mark &other);

/*
 *  �������� ���������� �� ���������� �� ������� ��������,
 *  ��������� � ���������� �����, ����� � ������� � ����������� ������
 */
    bool combination_is_closed(const GameView &game, Point nextPoint, Point prevPoint, const Line &line,
                               const Mark &pointMark);
}