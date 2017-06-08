def get_minimal(list, start)
  small = list[start]
  index = nil
  count = start
  size = list.size - start
  return start if size == 1
  size.times do ||
    if small > list[count]
      small = list[count]
      index = count
    end
    count += 1
  end
  index
end

def my_sort(list)
  count = 0
  temp = 0
  (list.size - 1).times do |n|
    puts 'n = ' + n.to_s
    min = get_minimal(list, n)
    if min
      puts "min =  #{list[min]}"
      temp = list[count]
      list[count] = list[min]
      puts "list[#{count}] = #{list[min]}"
      list[min] = temp
      count += 1
    end
  end
  list
end
l = [2, 3, 1, 7, 2, 5, 3]
# puts get_minimal(l, 5).to_s
l = my_sort(l)
puts l
