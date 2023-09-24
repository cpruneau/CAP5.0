/* **********************************************************************
 * Copyright (C) 2019-2022, Claude Pruneau, Victor Gonzalez, Sumit Basu
 * All rights reserved.
 *
 * Based on the ROOT package and environment
 *
 * For the licensing terms see LICENSE.
 *
 * Author: Claude Pruneau,   04/01/2022
 *
 * *********************************************************************/
#include "EventFilter.hpp"
using CAP::Filter;
using CAP::Event;
using CAP::EventFilter;

ClassImp(Filter<Event>);

ClassImp(EventFilter);

//!
//! CTOR
//!
EventFilter::EventFilter()
:
Filter<Event>()
{
  // no ops
}


//!
//! DTOR
//!
EventFilter::~EventFilter()
{
  // no ops
}

//!
//! accept/reject the given Event based on filter parameter
//!
bool EventFilter::accept(const Event & event)
{
  unsigned int nComponents = getNConditions();
  if (nComponents<1) return true;
  EventProperties * eventProperties = event.getEventProperties();
  if (!eventProperties) throw TaskException("Event does NOT have properties","EventFilter::accept(const Event & event)");
  double value;
  for (unsigned int k = 0; k<getNConditions(); k++)
    {
    Condition & condition = *(conditions[k]);
    unsigned index   = condition.filterSubtype;
    switch (condition.filterType)
      {
        case 10:
        // model parameter
        if (index>=eventProperties->modelParameters.size()) throw TaskException("index>=modelParameters.size()","EventFilter::accept(const Event & event)");
        value = eventProperties->modelParameters[index]; break;
        case 11:
        // filtered n
        if (index>=eventProperties->nFiltered.size()) throw TaskException("index>=eventProperties->nFiltered.size()","EventFilter::accept(const Event & event)");
        value = eventProperties->nFiltered[index]; break;
        case 12:
        // filtered energy
        if (index>=eventProperties->eFiltered.size()) throw TaskException("index>=eventProperties->eFiltered.size()","EventFilter::accept(const Event & event)");
        value = eventProperties->eFiltered[index]; break;
        case 13:
        // filtered charge
        if (index>=eventProperties->qFiltered.size()) throw TaskException("index>=eventProperties->qFiltered.size()","EventFilter::accept(const Event & event)");
        value = eventProperties->qFiltered[index]; break;
        case 14:
        // filtered strangeness
        if (index>=eventProperties->sFiltered.size())  throw TaskException("index>=eventProperties->sFiltered.size()","EventFilter::accept(const Event & event)");
        value = eventProperties->sFiltered[index]; break;
        case 15:
        // filtered baryoness
        if (index>=eventProperties->bFiltered.size()) throw TaskException("index>=eventProperties->bFiltered.size()","EventFilter::accept(const Event & event)");
        value = eventProperties->bFiltered[index]; break;
      }
//    cout << "            name: " << name << endl;
//    cout << "      filterType: " <<  condition.filterType << endl;
//    cout << "   filterSubtype: " <<  condition.filterSubtype << endl;
//    cout << "       nFiltered: " <<  eventProperties->nFiltered[index] << endl;
//    cout << "condition accept: " <<  condition.accept(value) << endl;

    if (!condition.accept(value))  return false;
    }
  return true;
}

