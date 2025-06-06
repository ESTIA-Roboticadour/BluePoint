#include "AppStore.h"
bool AppStore::s_isInEdition = false;

void AppStore::setIsInEdition(bool isInEdition) { s_isInEdition = isInEdition; }
bool AppStore::isInEdition() { return s_isInEdition; }
