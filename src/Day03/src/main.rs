use std::env; // For handling command line arguments
use std::fs; // For file operations
use std::io;
use std::process; // For terminating the program // For input/output operations and error handling

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        eprintln!("Usage: {} <file_path>", args[0]);
        process::exit(1);
    }
    let file_path = &args[1];

    match read_file_as_line_vector(file_path) {
        Ok(mut lines) => {
            let part1 = part_1(&mut lines.clone());
            println!("Part 1: {}", part1);
            let part2 = part_2(&mut lines);
            println!("Part 2: {}", part2);
        }
        Err(e) => {
            eprintln!("Error reading file: {}", e);
            process::exit(1);
        }
    }
}

fn part_1(lines: &mut Vec<Vec<u8>>) -> i32 {
    let mut sum = 0;
    for y in 0..lines.len() {
        for x in 0..lines[y].len() {
            if !lines[y][x].is_ascii_digit() && lines[y][x] != b'.' {
                sum += get_numbers_at_index(&mut lines[y - 1], x - 1);
                sum += get_numbers_at_index(&mut lines[y - 1], x);
                sum += get_numbers_at_index(&mut lines[y - 1], x + 1);
                sum += get_numbers_at_index(&mut lines[y], x - 1);
                sum += get_numbers_at_index(&mut lines[y], x + 1);
                sum += get_numbers_at_index(&mut lines[y + 1], x - 1);
                sum += get_numbers_at_index(&mut lines[y + 1], x);
                sum += get_numbers_at_index(&mut lines[y + 1], x + 1);
            }
        }
    }
    sum
}

fn part_2(lines: &mut Vec<Vec<u8>>) -> i32 {
    let mut sum = 0;
    for y in 0..lines.len() {
        for x in 0..lines[y].len() {
            if lines[y][x] == b'*' {
                let mut numbers = Vec::new();
                for (x, y) in get_surrounding_indexes(x, y).iter() {
                    numbers.push(get_numbers_at_index(&mut lines[*y], *x));
                }
                //remove 0s
                numbers.retain(|&x| x != 0);
                if numbers.len() == 2 {
                    sum += numbers[0] * numbers[1];
                }
            }
        }
    }
    sum
}

fn read_file_as_line_vector(path: &str) -> Result<Vec<Vec<u8>>, io::Error> {
    let contents = fs::read_to_string(path)?;
    let mut lines = Vec::new();
    for line in contents.lines() {
        lines.push(line.as_bytes().to_vec());
    }
    Ok(lines)
}

fn get_numbers_at_index(string: &mut Vec<u8>, x: usize) -> i32 {
    let mut start = x;
    let mut end = x;
    let mut number_found = false;
    while start > 0 && string[start] >= 48 && string[start] <= 57 {
        start -= 1;
        number_found = true;
    }
    if string[start] < 48 || string[start] > 57 {
        start += 1;
    }
    while end < string.len() && string[end] >= 48 && string[end] <= 57 {
        end += 1;
        number_found = true;
    }
    let mut number = 0;
    if number_found {
        number = String::from_utf8(string[start..end].to_vec())
            .unwrap()
            .parse::<i32>()
            .unwrap();
    }
    for i in start..end {
        string[i] = b'.'; // Replace with '.' character
    }
    number
}

fn get_surrounding_indexes(x: usize, y: usize) -> [(usize, usize); 8] {
    [
        (x - 1, y - 1),
        (x, y - 1),
        (x + 1, y - 1),
        (x - 1, y),
        (x + 1, y),
        (x - 1, y + 1),
        (x, y + 1),
        (x + 1, y + 1),
    ]
}
