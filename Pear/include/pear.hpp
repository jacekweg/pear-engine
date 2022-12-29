#pragma once
#include "pch.hpp"
#include "start.hpp"
#include "commands.hpp"
#include "utils/logging.hpp"
#include "events/event_controller.hpp"
#include <glad/glad.h>

std::unique_ptr<Pear::Application> Pear::CreateUserApp();