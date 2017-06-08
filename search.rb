def bins(list, target)
  guess = list.length / 2
  min = 0
  max = list.length - 1
  while target
    if (max - min).zero?
      return true if list[min] == target
      return false
    end
    if list[guess] == target
      puts 'SUCESS'
      return true
    elsif list[guess] < target
      puts "target is bigger #{list[guess]}"
      min = guess + 1
    elsif list[guess] > target
      puts "target is smaller than #{list[guess]}"
      max = guess - 1
    end
    guess = (max + min) / 2
  end
  puts 'false'
  false
end

bins [1, 2, 3, 4, 5, 6, 7, 8], 8
puts 'found' if bins [1, 2, 3, 4, 5, 6, 7, 8], 9
