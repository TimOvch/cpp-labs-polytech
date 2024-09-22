#include "Analyzer.h"
#include <vector>

namespace ovchinnikov_2 {
    Point line_inc(const Point &point, const Line &line) {
        int retX, retY;

        switch (line) {
            case Vertical:
                retY = point.y + 1;
                retX = point.x;
                break;
            case ThirdToFirst:
                retY = point.y + 1;
                retX = point.x + 1;
                break;
            case Horizontal:
                retY = point.y;
                retX = point.x + 1;
                break;
            case SecondToFourth:
                retY = point.y - 1;
                retX = point.x + 1;
                break;
            default:
                retY = point.y;
                retX = point.x;
                break;
        }

        return Point{retX, retY};
    }

    Point line_dec(const Point &point, const Line &line) {
        int retX, retY;

        switch (line) {
            case Vertical:
                retY = point.y - 1;
                retX = point.x;
                break;
            case ThirdToFirst:
                retY = point.y - 1;
                retX = point.x - 1;
                break;
            case Horizontal:
                retY = point.y;
                retX = point.x - 1;
                break;
            case SecondToFourth:
                retY = point.y + 1;
                retX = point.x - 1;
                break;
            default:
                retY = point.y;
                retX = point.x;
                break;
        }

        return Point{retX, retY};
    }

    Mark opp_mark(const Mark &mark) {
        return (mark == Mark::Cross) ? Mark::Zero : Mark::Cross;
    }

    int point_to_int(const Point &point) {
        /*
         * —оздаЄт уникальное число дл€ каждой точки в пространстве
         * Ќеобходима дл€ работы map
         * Ќа выходе получаетс€ шестизначное число:
         * ѕервый с лева разр€д отвечает за знак x
         * ¬торой с лева разр€д отвечает за знак y
         * ¬торой и четвертый разр€ды - модуль координаты по x
         * ѕ€тый и шестой - модуль координаты по y
         */
        int ret = abs(point.x) * 100 + abs(point.y);
        if (point.x < 0) {
            ret += 100000;
        }
        if (point.y < 0) {
            ret += 10000;
        }

        return ret;
    }

    double count_price(const PointPriceInfo &pointInfo, const double &alpha, const Status &prevStatus,
                       const Status &pointStatus) {
        double price = 0;

        switch (pointInfo.power) {
            case 5:
                if (pointStatus == Attack) {
                    price = pow(alpha, 3) * 8192 * basic_price;
                } else {
                    price = pow(alpha, 3) * 1024 * basic_price;
                }
                break;
            case 4:
                if (pointStatus == Attack) {
                    if (pointInfo.combination == Full) {
                        price = pow(alpha, 3) * 128 * basic_price;
                    } else if (prevStatus == Defence && pointInfo.distance == 0) {
                        price = pow(alpha, 3) * 2 * basic_price;
                    } else {
                        price = pow(alpha, 3) * basic_price;
                    }
                } else {
                    if (pointInfo.combination == Full) {
                        price = pow(alpha, 3) * 16 * basic_price;
                    } else {
                        price = pow(alpha, 3) * basic_price;
                    }
                }
                break;
            case 3:
                if (pointStatus == Attack) {
                    if (pointInfo.combination != Full) {
                        price = pow(alpha, 2) * basic_price;
                    } else if (prevStatus == Attack) {
                        price = pow(alpha, 3) * basic_price;
                    } else {
                        price = pow(alpha, 3) * 2 * basic_price;
                    }
                } else {
                    if (pointInfo.combination == Full) {
                        price = pow(alpha, 3) * basic_price;
                    } else {
                        price = pow(alpha, 2) * basic_price;
                    }
                }
                break;
            case 2:
                if (pointInfo.combination == Full) {
                    price = pow(alpha, 2) * basic_price;
                } else {
                    price = alpha * basic_price;
                }
                break;
            case 1:
                if (pointInfo.combination == Full) {
                    price = alpha * basic_price;
                } else {
                    price = basic_price;
                }
                break;
        }
        price = price * (1 - pointInfo.distance * beta);

        if (pointInfo.between) {
            price = price / 2;
        }

        return price;
    }

    Status mark_to_status(const Mark &myMark, const Mark &other) {
        return (myMark == other) ? Attack : Defence;
    }

    bool combination_is_closed(const GameView &game, Point nextPoint, Point prevPoint, const Line &line,
                               const Mark &pointMark) {
        short len_betw_opp_marks = 1;
        short len_inc = 0;
        short len_dec = 0;

        while (len_inc != game.get_settings().win_length &&
               is_in_bound(nextPoint) && get_val(nextPoint) != opp_mark(pointMark)) {
            len_inc++;
            nextPoint = line_inc(nextPoint, line);
        }

        while (len_dec != game.get_settings().win_length &&
               is_in_bound(prevPoint) && get_val(prevPoint) != opp_mark(pointMark)) {
            len_dec++;
            prevPoint = line_dec(prevPoint, line);
        }

        if (len_inc + len_dec + len_betw_opp_marks < game.get_settings().win_length) {
            return true;
        } else {
            return false;
        }
    }


// PointData методы:

    PointData::PointData()
            : used_lines() {
        def_price = 0;
        att_price = 0;
        for (bool &used_line: used_lines) {
            used_line = false;
        }
        mark = Mark::None;
    }

    double PointData::get_price() const {
        return def_price + att_price;
    }

    Status PointData::get_status() const {
        return (def_price > att_price) ? Defence : Attack;
    }

    bool PointData::is_line_used(const Line &line) {
        bool temp = used_lines[line];
        return temp;
    }

    void PointData::add_price(const double &price, const Status &status) {
        (status == Attack) ? att_price += price : def_price += price;
    }

    void PointData::marked(const Mark &incomeMark, const Line &line) {
        mark = incomeMark;
        used_lines[line] = true;
    }

    //comp оператор:

    bool comp::operator()(const Point &point1, const Point &point2) const {
        return point_to_int(point1) < point_to_int(point2);
    }

// PointDataContainer методы:

    PointDataContainer::PointDataContainer()
            : data(), max_price(0), max_price_point(), max_price_status(Attack) {}

    Point PointDataContainer::get_max_point() const {
        return max_price_point;
    }

    Status PointDataContainer::get_max_status() const {
        return max_price_status;
    }

    void PointDataContainer::add_price(const Point &point, const double &price, const Status &status) {
        data[point].add_price(price, status);
        double checking = data[point].get_price();
        if ((checking > max_price) ||
            ((checking == max_price) && (rand() % 2))) { // если цена данной больше или равна и рандом
            max_price = checking;
            max_price_point = point;
            max_price_status = data[point].get_status();
        }
    }

    void PointDataContainer::marked(const Point &point, const Mark &mark, const Line &line) {
        data[point].marked(mark, line);
    }

    bool PointDataContainer::is_line_used(const Point &point, const Line &line) {
        return data[point].is_line_used(line);
    }

// Analyzer методы:
    Analyzer::Analyzer(const Status &prevStatus, const Mark &myMark, const double &alpha)
            : prevStatus(prevStatus), myMark(myMark), alpha(alpha), container() {}

    Point Analyzer::decision() const {
        return container.get_max_point();
    }

    Status Analyzer::next_prev_status() const {
        return container.get_max_status();
    }

    void Analyzer::get_sells_and_prices(const GameView &game, SellAndPricesInfo &info) {
        for (short dist = 0; dist < game.get_settings().win_length - info.power; dist++) {
            if (is_opp_or_edge(info.dir(info.directionPoint, info.line), info.pointMark)) {
                Combination tempComb = Half;

                PointPriceInfo ppi{info.directionPoint, (short) (info.power + 1), tempComb, dist, false};
                double price = count_price(ppi, alpha, prevStatus, mark_to_status(myMark, info.pointMark));
                container.add_price(ppi.point, price, mark_to_status(myMark, info.pointMark));

                break;
            } else if (is_same_mark(info.dir(info.directionPoint, info.line), info.pointMark)) {
                Combination tempComb = Full;

                if (is_opp_or_edge(info.dir(info.dir(info.directionPoint, info.line), info.line), info.pointMark)) {
                    tempComb = Half;
                }

                PointPriceInfo ppi{info.directionPoint, (short) (info.power + 2), tempComb, dist, true};
                double price = count_price(ppi, alpha, prevStatus, mark_to_status(myMark, info.pointMark));
                container.add_price(ppi.point, price, mark_to_status(myMark, info.pointMark));

                break;
            } else {
                PointPriceInfo ppi{info.directionPoint, (short) (info.power + 1), info.combination, dist, false};
                double price = count_price(ppi, alpha, prevStatus, mark_to_status(myMark, info.pointMark));
                container.add_price(ppi.point, price, mark_to_status(myMark, info.pointMark));
            }
            info.directionPoint = info.dir(info.directionPoint, info.line);
        }
    }

    void Analyzer::lines_checker(const GameView &game, const Point &main, const Mark &pointMark) {
        for (int _ = 0; _ < 4; _++) {
            Line line = (Line) _;
            Point next = line_inc(main, line);
            Point prev = line_dec(main, line);
            if (container.is_line_used(main, line) || is_not_edge(next, prev) ||
                combination_is_closed(game, next, prev, line, pointMark)) {
                continue;
            }

            Point (*power_dir)(const Point &, const Line &);
            Point (*edge_dir)(const Point &, const Line &);

            if ((is_in_bound(next)) && (get_val(next) != Mark::None) || (!is_in_bound(next))) {
                power_dir = line_inc;
                edge_dir = line_dec;
            } else {
                power_dir = line_dec;
                edge_dir = line_inc;
            }

            short power = 1;
            Combination combination = Full;
            Point pdPoint = power_dir(main, line);
            Point edPoint = edge_dir(main, line);
            while (true) {
                if (!is_in_bound(pdPoint) || (is_in_bound(pdPoint)) && (get_val(pdPoint) == opp_mark(pointMark))) {
                    combination = Half;
                    break;
                } else if ((is_in_bound(pdPoint)) && (get_val(pdPoint) == Mark::None)) {
                    break;
                } else {
                    container.marked(pdPoint, pointMark, line);
                    pdPoint = power_dir(pdPoint, line);
                    power++;
                }
            }

            if (combination != Half) {
                SellAndPricesInfo infoPowerDir{power, power_dir, pointMark, pdPoint, line, combination};
                get_sells_and_prices(game, infoPowerDir);
            }

            SellAndPricesInfo infoEdgeDir{power, edge_dir, pointMark, edPoint, line, combination};
            get_sells_and_prices(game, infoEdgeDir);
        }
    }

    void Analyzer::analyze(const GameView &game) {

        if (game.get_state().number_of_moves == 0) {
            int centx = (min_p.x + max_p.x) / 2;
            int centy = (min_p.y + max_p.y) / 2;
            Point center{centx, centy};

            container.add_price(center, CENTER_PRICE_CONSTANT, Attack);

            return;
        }

        auto iter = game.get_state().field->get_iterator();
        while (iter->has_value()) {
            Point main = iter->get_point();
            Mark pmark = get_val(main);

            lines_checker(game, main, pmark);

            iter->step();
        }
    }
}