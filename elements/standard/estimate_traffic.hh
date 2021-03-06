// -*- c-basic-offset: 4 -*-
#ifndef CLICK_ESTIMATE_TRAFFIC_HH
#define CLICK_ESTIMATE_TRAFFIC_HH
#include <click/element.hh>
#include <click/timer.hh>
#include <pthread.h>
#include <unordered_map>
#include "fullnotelockqueue.hh"
#include "solstice.hh"
CLICK_DECLS

/*
=c

EstimateTraffic()

=s control

Estimates OCS Traffic

=d

TODO

=h

*/

#define ADU_PORT "8123"

class EstimateTraffic : public Element {
  public:
    EstimateTraffic() CLICK_COLD;

    const char *class_name() const	{ return "EstimateTraffic"; }
    int configure(Vector<String> &, ErrorHandler *) CLICK_COLD;
    int initialize(ErrorHandler *) CLICK_COLD;
    void add_handlers() CLICK_COLD;

    bool run_task(Task *);
    String source;
    String *output_traffic_matrix;

  private:
    static int set_source(const String&, Element*, void*, ErrorHandler*) CLICK_COLD;
    static int clear(const String&, Element*, void*, ErrorHandler*) CLICK_COLD;
    static String get_traffic(Element *e, void *user_data);

    int _serverSocket;
    fd_set _active_fd_set;

    int _queue_clear_timeout;
    struct timespec _last_queue_clear;

    int _num_hosts;

    long long *_traffic_matrix;
    Task _task;
    int _print;

    FullNoteLockQueue **_queues;
    Solstice *_solstice;

    pthread_mutex_t _lock;
    pthread_mutex_t _adu_lock;
    std::unordered_map<const struct traffic_info, long long, info_key_hash, info_key_equal> expected_adu;
};

CLICK_ENDDECLS
#endif
