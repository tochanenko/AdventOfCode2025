package day01

import readLines
import kotlin.math.round
import kotlin.math.abs
import kotlin.math.sign

fun main(args: Array<String>) {
    val lines = readLines("./src/main/kotlin/day01/input.txt")
    println(passwordEnhanced(lines))
}

fun password(lines: List<String>): Int {
    var res = 0
    var currentPosition = 50
    for (line in lines) {
        currentPosition = rotate(
            currentPosition,
            (if (line[0] == 'L') -1 else 1) * line.substring(1).toInt()
        )
        if (currentPosition == 0) res++
    }
    return res
}

fun rotate(position: Int, amount: Int): Int = (position + amount) % 100

fun passwordEnhanced(lines: List<String>): Int {
    var res = 0
    var currentPosition = 50
    for (line in lines) {
        val (newPosition, toAdd) = rotateEnhanced(
            currentPosition,
            (if (line[0] == 'L') -1 else 1) * line.substring(1).toInt()
        )
        currentPosition = newPosition
        res += toAdd
    }
    return res
}

fun rotateEnhanced(position: Int, amount: Int): Pair<Int, Int> {
    var score = 0
    var res = position
    for (i in 0 until abs(amount)) {
        res += sign(amount.toDouble()).toInt() * 1
        if (res == -1) res = 99
        if (res == 100) res = 0
        if (res == 0) score++

    }
    return Pair(res, score)
}