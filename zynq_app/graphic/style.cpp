#include "style.h"

Style& Style::getInstance()
{
    static Style instance;
    return instance;
}

Style::Style()
{

}
