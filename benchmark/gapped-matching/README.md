Benchmarks for paper "Practical Variable Length Gap Pattern Matching" (SEA 2016, http://link.springer.com/chapter/10.1007/978-3-319-38851-9_1). Based on https://github.com/simongog/sdsl-lite

INSTALL

1. git submodule update --init
2. mkdir build
3. cd build
4. cmake .. && make

CREATE COLLECTIONS

1. cd build
2. ./create-collection.x -c ../collection/NEWNAME -i NEWNAME.raw

EXECUTE BENCHMARK

1. cd build
2. ./gm_index-YOUR_IDX.x -c ../collections/your_collection
3. ./gm_search-YOUR_IDX.x -c ../collections/your_collection -p ../collections/your_collection/patterns/your_pattern.txt

TROUBLESHOOTING AND NOTES

- Make sure sdsl is installed first. That is, before step 1 of "INSTALL", run ./install.sh in the main sdsl directory.
- For the syntax of the pattern, see [utils.hpp](https://github.com/olydis/vlg_matching/blob/master/benchmark/gapped-matching/include/utils.hpp). For example, bla.{3,5}blub is valid syntax.
