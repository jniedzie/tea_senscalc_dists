#ifndef SCHistogramsFiller_hpp
#define SCHistogramsFiller_hpp

#include "Event.hpp"
#include "EventProcessor.hpp"
#include "Helpers.hpp"
#include "HistogramsHandler.hpp"

class SCHistogramsFiller {
 public:
  SCHistogramsFiller(std::shared_ptr<HistogramsHandler> histogramsHandler_);
  ~SCHistogramsFiller();

  void Fill(const std::shared_ptr<Event> event);

 private:
  std::shared_ptr<HistogramsHandler> histogramsHandler;
  std::unique_ptr<EventProcessor> eventProcessor;
  std::string weightsBranchName;

  float GetWeight(const std::shared_ptr<Event> event);
};

#endif /* SCHistogramsFiller_hpp */
