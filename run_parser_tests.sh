#!/bin/bash

# Parser Test Suite for cub3d
# Tests valid and invalid .cub files

echo "╔═══════════════════════════════════════════════════════════════════╗"
echo "║                    CUB3D PARSER TEST SUITE                        ║"
echo "╚═══════════════════════════════════════════════════════════════════╝"
echo ""

PASS=0
FAIL=0

# Function to run test
run_test() {
    local file=$1
    local should_pass=$2
    local test_name=$3
    
    echo -n "Testing: $test_name ... "
    
    if ./test_parser "$file" > /dev/null 2>&1; then
        if [ "$should_pass" = "true" ]; then
            echo "✓ PASS"
            ((PASS++))
        else
            echo "✗ FAIL (should have failed)"
            ((FAIL++))
        fi
    else
        if [ "$should_pass" = "false" ]; then
            echo "✓ PASS (correctly rejected)"
            ((PASS++))
        else
            echo "✗ FAIL (should have passed)"
            ((FAIL++))
        fi
    fi
}

echo "═══════════════════════════════════════════════════════════════════"
echo "VALID FILES (should pass)"
echo "═══════════════════════════════════════════════════════════════════"

run_test "test_files/file.cub" "true" "Basic map with player N"
run_test "test_files/room.cub" "true" "Room map with player N"
run_test "test_files/big.cub" "true" "Large complex map"
run_test "test_files/valid_door.cub" "true" "Map with doors (bonus)"

echo ""
echo "═══════════════════════════════════════════════════════════════════"
echo "INVALID FILES (should fail)"
echo "═══════════════════════════════════════════════════════════════════"

run_test "test_files/invalid_duplicate_texture.cub" "false" "Duplicate texture"
run_test "test_files/invalid_missing_texture.cub" "false" "Missing required texture"
run_test "test_files/invalid_rgb_out_of_range.cub" "false" "RGB value > 255"
run_test "test_files/invalid_no_player.cub" "false" "No player in map"
run_test "test_files/invalid_multiple_players.cub" "false" "Multiple players"
run_test "test_files/invalid_not_enclosed.cub" "false" "Map not enclosed by walls"
run_test "test_files/maze.cub" "false" "Maze with missing walls"

if [ -f "test_files/invalid_empty_line.cub" ]; then
    run_test "test_files/invalid_empty_line.cub" "false" "Empty line in map"
fi

echo ""
echo "═══════════════════════════════════════════════════════════════════"
echo "SUMMARY"
echo "═══════════════════════════════════════════════════════════════════"
echo "Passed: $PASS"
echo "Failed: $FAIL"
TOTAL=$((PASS + FAIL))
echo "Total:  $TOTAL"
echo ""

if [ $FAIL -eq 0 ]; then
    echo "✓ All tests passed!"
    exit 0
else
    echo "✗ Some tests failed"
    exit 1
fi
