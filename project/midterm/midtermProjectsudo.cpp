cin>>

while (zeroNum == 0)
{
	findMax()
	findMin()
	assignFull(maxPos)  // 從最大值開始扣 
	fullNum += min
	zeroNum = countZero()	
}

while (zeroNum == 1)
{
	zeroPos[0] = zeroAdress();
	findMin()
	assignFull(zeroPos[0] + 1)  // 從0右邊開始扣 
	fullNum += min
	zeroNum = countZero()		
}

while (zeroNum == 2)
{
	findMin()
	zeroPos[1] = zeroAdress() 
	if zeroAdjacent == 1  // 0相鄰  
		assignFull(zeroPos[1] + 1)  // 從0右邊開始扣 
	else // 0不相鄰 
		if (partWage <= compen)  // part-time便宜 
			assignFull(zeroPos[1] + 1) 
		else
			assignFullCompen()
	fullNum += min
	zeroNum = countZero()
}

while (zeroNum >= 3 && zeroNum > 7 - ratioFP)
{
	int startPos = 0
	findMin()
	if (fullNum < fullHired)  // 如果有剩
		startPos = fivesumMax()
		assignFull(startPos, fullHired - fullNum, )
		fullNum += fullHired - fullNum
	else  // 沒剩
		if partWage <= compen
			assignFull(minPosm, min) // 從最小值位置開始扣最小值 
		else
			assignFullCompen
		fullNum += min	
	
	zeroNum = countZero
}

if (zeroNum <= 7 - ratioFP)
{
	if (fullNum < fullHired)  // 如果有剩
		startPos = fivesumMax()
		assignFull(startPos, fullHired - fullNum, )
		fullNum += fullHired - fullNum
	else
		assignPart()
		break	
}

output()
