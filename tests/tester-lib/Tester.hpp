/**
 * Copyright (C) 2024-2025 Gianmarco Lenzi
 * Licensed under MIT as part of the DSK Project, see LICENSE file for details.
 * A copy of the license can be found at: https://opensource.org/licenses/MIT.
 *
 * @file Tester.hpp
 * @author Gianmarco Lenzi
 * @brief Header for tester class.
 */

#pragma once
#include "common.hpp"
#include "Results.hpp"

namespace Testers {
    /**
     * @brief Base class for testers.
     */
    class Tester {
        public:
            /**
             * @brief Virtual destructor.
             */
            virtual ~Tester() = default;

            /**
             * @brief Gets the name of the tester.
             * @return The name.
             */
            virtual std::string get_name() const = 0;

            /**
             * @brief Gets the fully qualified name of the tester.
             * @return The fully qualified name.
             */
            virtual std::string get_full_name() const = 0;

            /**
             * @brief Gets the results of the tester.
             * @return The results.
             */
            virtual Results get_results() const = 0;
    };

} // Testers
