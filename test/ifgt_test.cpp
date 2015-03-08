#include <fgt/ifgt.hpp>

#include "clustering/gonzalez.hpp"
#include "clustering.hpp"
#include "config.hpp"
#include "parameters.hpp"

#include <armadillo>
#include <gtest/gtest.h>


namespace fgt {


TEST(Ifgt, ReferenceImplementation) {
    arma::mat X;
    X.load(test_data_path("X.csv"));
    arma::mat Y;
    Y.load(test_data_path("Y.csv"));

    double h = 0.4;
    double epsilon = 1e-3;
    arma::vec q = arma::ones<arma::vec>(X.n_rows);

    Parameters params = choose_parameters(X.n_cols, h, epsilon, 50);
    Clustering clustering =
        gonzalez_clustering(X, params.K, h, epsilon, true, 2);
    clustering.initialize();

    arma::vec G = ifgt(clustering, Y, h, q, params);

    EXPECT_EQ(G.n_rows, 5000);
    EXPECT_NEAR(359.4559, arma::min(G), 0.0001);
    EXPECT_NEAR(2.2214e3, arma::max(G), 0.1);
}
}
