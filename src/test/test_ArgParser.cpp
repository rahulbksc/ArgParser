#ifndef CATCH_INCLUDED
#define CATCH_INCLUDED
#include "catch.hpp"
#endif
#include "../ArgParser.hpp"

TEST_CASE("Single Dash with Equals")
{
	int argc = 2;
	char *argv[] = {
					"argParserTest",
					"-filename=file1.dat",
					NULL
	};
	std::string filename;

	ArgParser parser(argc, argv);
	parser.get("filename", filename);

	REQUIRE(filename == "file1.dat");
}

TEST_CASE("Double Dash with Equals")
{
	int argc = 2;
	char *argv[] = {
					"argParserTest",
					"--filename=file1.dat",
					NULL
	};
	std::string filename;

	ArgParser parser(argc, argv);
	parser.get("filename", filename);

	REQUIRE(filename == "file1.dat");
}

TEST_CASE("Single Dash without Equals")
{
	int argc = 3;
	char *argv[] = {
					"argParserTest",
					"-filename",
					"file1.dat",
					NULL
	};
	std::string filename;

	ArgParser parser(argc, argv);
	parser.get("filename", filename);

	REQUIRE(filename == "file1.dat");
}

TEST_CASE("Double Dash without Equals")
{
	int argc = 3;
	char *argv[] = {
					"argParserTest",
					"--filename",
					"file1.dat",
					NULL
	};
	std::string filename;

	ArgParser parser(argc, argv);
	parser.get("filename", filename);

	REQUIRE(filename == "file1.dat");
}

TEST_CASE("String Arg")
{
	int argc = 2;
	char *argv[] = {
					"argParserTest",
					"--filename=file1.dat",
					NULL
	};
	std::string filename;

	ArgParser parser(argc, argv);
	parser.get("filename", filename);

	REQUIRE(filename == "file1.dat");
}

TEST_CASE("Int Arg")
{
	int argc = 2;
	char *argv[] = {
					"argParserTest",
					"--warpFactor=8",
					NULL
	};
	int warpFactor;

	ArgParser parser(argc, argv);
	parser.get("warpFactor", warpFactor);

	REQUIRE(warpFactor == 8);
}

TEST_CASE("Double Arg")
{
	int argc = 2;
	char *argv[] = {
					"argParserTest",
					"--warpFactor=9.5",
					NULL
	};
	double warpFactor;

	ArgParser parser(argc, argv);
	parser.get("warpFactor", warpFactor);

	REQUIRE(warpFactor == 9.5);
}

TEST_CASE("Bool Arg")
{
	int argc = 2;
	char *argv[] = {
					"argParserTest",
					"--verbose",
					NULL
	};
	bool verbose;

	ArgParser parser(argc, argv);
	parser.get("verbose", verbose);

	REQUIRE(verbose == true);
}