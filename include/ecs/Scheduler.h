#pragma once

#include <array>
#include "Schedule.h"
#include "ScheduleGraph.h"

class Scheduler {
public:
    explicit Scheduler(auto &scdl) : schedules(scdl) {
    }

    template<typename System>
    SystemScheduler AddSystem(const Schedule schedule);

    template<typename First, typename Second, typename... Others>
    SystemScheduler Chain(const Schedule schedule);

private:
    template<typename First, typename Second, typename... Others>
    void AddEdges(ScheduleGraph &graph);

    std::array<ScheduleGraph, Schedule::ScheduleSize> &schedules;
    template<typename First, typename Last>
    class SystemScheduler;
};

template<typename First, typename Last>
class Scheduler::SystemScheduler {
public:
    explicit SystemScheduler
    (ScheduleGraph &scdl) : schedule(scdl) {
    }

    template<typename T>
    Scheduler After();

    template<typename T>
    Scheduler Before();

private:
    ScheduleGraph &schedule;
};

template<typename System>
SystemScheduler Scheduler::AddSystem(const Schedule schedule) {
    auto &graph = schedules[schedule];
    graph.AddNode<System>();
    return SystemScheduler<System, System>(schedule);
}

template<typename First, typename Second, typename... Others>
SystemScheduler Scheduler::Chain(const Schedule schedule) {
    auto &graph = schedules[schedule];
    graph.AddNode<First>();
    graph.AddNode<Second>();
    (void(graph.AddNode<Others>()), ...);
    graph.AddEdge<First, Second>();
    if (sizeof...(Others) > 0) {
        AddEdges<Second, Others...>(graph);
        using Last = std::tuple_element_t<sizeof...(Others) - 1, std::tuple<Others...> >;
        return SystemScheduler<First, Last>(graph);
    }
    return SystemScheduler<First, Second>(graph);
}

template<typename First, typename Second, typename... Others>
void Scheduler::AddEdges(ScheduleGraph &graph) {
    graph.AddEdge<First, Second>();
    if (sizeof...(Others) > 0) {
        AddEdges<Second, Others...>(graph);
    }
}

template<typename First, typename Last>
template<typename T>
Scheduler Scheduler::SystemScheduler<First, Last>::After() {
    schedule.AddEdge<T, First>();
}

template<typename First, typename Last>
template<typename T>
Scheduler Scheduler::SystemScheduler<First, Last>::Before() {
    schedule.AddEdge<Last, T>();
}

