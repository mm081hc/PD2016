cin>>

while (zeroNum == 0)
{
	findMax()
	findMin()
	assignFull(maxPos)  // �q�̤j�ȶ}�l�� 
	fullNum += min
	zeroNum = countZero()	
}

while (zeroNum == 1)
{
	zeroPos[0] = zeroAdress();
	findMin()
	assignFull(zeroPos[0] + 1)  // �q0�k��}�l�� 
	fullNum += min
	zeroNum = countZero()		
}

while (zeroNum == 2)
{
	findMin()
	zeroPos[1] = zeroAdress() 
	if zeroAdjacent == 1  // 0�۾F  
		assignFull(zeroPos[1] + 1)  // �q0�k��}�l�� 
	else // 0���۾F 
		if (partWage <= compen)  // part-time�K�y 
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
	if (fullNum < fullHired)  // �p�G����
		startPos = fivesumMax()
		assignFull(startPos, fullHired - fullNum, )
		fullNum += fullHired - fullNum
	else  // �S��
		if partWage <= compen
			assignFull(minPosm, min) // �q�̤p�Ȧ�m�}�l���̤p�� 
		else
			assignFullCompen
		fullNum += min	
	
	zeroNum = countZero
}

if (zeroNum <= 7 - ratioFP)
{
	if (fullNum < fullHired)  // �p�G����
		startPos = fivesumMax()
		assignFull(startPos, fullHired - fullNum, )
		fullNum += fullHired - fullNum
	else
		assignPart()
		break	
}

output()
