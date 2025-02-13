Approach - How This Works
Binary Search for Fast Lookup

Instead of reading the entire 1TB file, we use binary search to jump to the first occurrence of the given date.
This reduces the time complexity from O(N) to O(log N), making it super fast.
Jump to the Exact Position

After finding the approximate position, we adjust to the nearest new line to avoid reading partial logs.
Extract Only the Required Logs

Once we reach the target date, we start reading logs line by line.
We stop as soon as we encounter a different date, avoiding unnecessary reads.
Write Output Efficiently

The extracted logs are saved in ../output/output_YYYY-MM-DD.txt.

Usage

./extract_logs ../logs.txt 2024-12-01

Output is stored in root/output/output_2024-12-01.txt.