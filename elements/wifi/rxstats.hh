#ifndef CLICK_RXSTATS_HH
#define CLICK_RXSTATS_HH
#include <click/element.hh>
#include <click/etheraddress.hh>
#include <click/bighashmap.hh>
#include <click/glue.hh>
CLICK_DECLS

/*
 * =c
 * 
 * RXStats()
 * 
 * =s wifi
 * 
 * Accumulate rxstats for each ethernet src you hear a packet from.
 * =over 8
 *
 *
 */


class RXStats : public Element { public:
  
  RXStats();
  ~RXStats();
  
  const char *class_name() const		{ return "RXStats"; }
  const char *processing() const		{ return AGNOSTIC; }
  
  int configure(Vector<String> &, ErrorHandler *);
  bool can_live_reconfigure() const		{ return true; }

  Packet *simple_action(Packet *);

  void add_handlers();

  class DstInfo {
  public:
    EtherAddress _eth;
    int _rate;
    int _noise;
    int _signal;

    int _packets;
    unsigned _sum_signal;
    unsigned _sum_noise;
    struct timeval _last_received;
    
    DstInfo() { 
      memset(this, 0, sizeof(*this));
    }

    DstInfo(EtherAddress eth) { 
      memset(this, 0, sizeof(*this));
      _eth = eth;
    }

  };
  typedef HashMap<EtherAddress, DstInfo> NeighborTable;
  typedef NeighborTable::const_iterator NIter;

  class NeighborTable _neighbors;
  EtherAddress _bcast;
  int _tau;


};

CLICK_ENDDECLS
#endif
