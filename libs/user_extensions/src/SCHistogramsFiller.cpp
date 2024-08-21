#include "SCHistogramsFiller.hpp"

#include "ConfigManager.hpp"
#include "ExtensionsHelpers.hpp"

using namespace std;

SCHistogramsFiller::SCHistogramsFiller(shared_ptr<HistogramsHandler> histogramsHandler_) : histogramsHandler(histogramsHandler_) {
  // Create a config manager
  auto &config = ConfigManager::GetInstance();

  // Try to read weights branch
  try {
    config.GetValue("weightsBranchName", weightsBranchName);
  } catch (const Exception& e) {
    info() << "Weights branch not specified -- will assume weight is 1 for all events" << endl;
  }

  // Create an event processor
  eventProcessor = make_unique<EventProcessor>();
}

SCHistogramsFiller::~SCHistogramsFiller() {}

float SCHistogramsFiller::GetWeight(const std::shared_ptr<Event> event) {
  // Try to get event weight, otherwise set to 1.0
  float weight = 1.0;
  try {
    weight = event->Get(weightsBranchName);
  } catch (const Exception &e) {
  }
  return weight;
}

void SCHistogramsFiller::Fill(const std::shared_ptr<Event> event) {
  // Fill the histogram for given event (e.g. use EventProcessor to get some variables)
  histogramsHandler->Fill("test", eventProcessor->GetMaxPt(event, "Muon"), GetWeight(event));
}
