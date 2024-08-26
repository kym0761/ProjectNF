// Fill out your copyright notice in the Description page of Project Settings.


#include "Data.h"

FItemSheetData::FItemSheetData()
	:Thumbnail(nullptr),
	bIsStackable(true),
	MaxQuantity(1000),
	ItemType(EItemType::None),
	ItemRarity(EItemRarity::Normal),
	ItemPrice(1),
	ItemMesh(nullptr)
{

}

bool FItemSheetData::IsEmpty()
{
	//ItemBaseData의 이름의 빈 값은 아무 정보도 아닌 것으로 판정함.
	return ItemNameID.IsEmpty();
}



FItemSlotData::FItemSlotData() :ItemName(""), Quantity(0)
{

}

bool FItemSlotData::IsSameItem(const FItemSlotData& Other) const
{
	return ItemName.IsEqual(Other.ItemName);
}

bool FItemSlotData::IsEmpty() const
{
	return ItemName.IsNone() || ItemName.GetStringLength() == 0;
}

void FItemSlotData::SetEmpty()
{
	ItemName = "None";
	Quantity = 0;
}

FShopItemData::FShopItemData()
{
	ItemName = FName(TEXT(""));
	Price = 0;
	Stock = 0;
}

//~~

FGrid::FGrid()
{
	X = 0;
	Y = 0;
}

FGrid::FGrid(int32 _X, int32 _Y)
{
	X = _X;
	Y = _Y;
}

FString FGrid::ToString() const
{
	return FString("X : ") + FString::FromInt(X) + FString(" / Y : ") + FString::FromInt(Y);
}

bool FGrid::operator==(const FGrid& Other) const
{
	return X == Other.X && Y == Other.Y;
}

bool FGrid::operator!=(const FGrid& Other) const
{
	return !(*this == Other);
}

FGrid FGrid::operator+(const FGrid& b) const
{
	FGrid temp;
	temp.X = X + b.X;
	temp.Y = Y + b.Y;
	return temp;
}

FGrid FGrid::operator -(const FGrid& b) const
{
	FGrid temp;
	temp.X = X - b.X;
	temp.Y = Y - b.Y;
	return temp;
}

FGrid& FGrid::operator=(const FGrid& b)
{
	X = b.X;
	Y = b.Y;

	return *this;
}

FGrid& FGrid::operator+=(const FGrid& b)
{
	(*this) = (*this) + b;
	return *this;
}

FGrid& FGrid::operator-=(const FGrid& b)
{
	(*this) = (*this) - b;
	return *this;
}

int32 FGrid::Size() const
{
	return FMath::Abs(X) + FMath::Abs(Y);
}

bool FGrid::IsInvalidGrid() const
{
	return X < 0 || Y < 0;
}

uint32 GetTypeHash(const FGrid& Grid)
{
	return FCrc::MemCrc32(&Grid, sizeof(Grid));
}

//~~

//[0]번째는 편의상 사용하지 않는다.
const TArray<int32> FGameDateTime::MAXDAY_OF_MONTH = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

const FGameDateTime FGameDateTime::MORNING = FGameDateTime(0, 0, 0, 6, 0);
const FGameDateTime FGameDateTime::NOON = FGameDateTime(0, 0, 0, 12, 0);
const FGameDateTime FGameDateTime::EVENING = FGameDateTime(0, 0, 0, 18, 0);

FGameDateTime::FGameDateTime(int32 InYear, int32 InMonth, int32 InDay, int32 InHour, int32 InMinute)
{
	Year = FMath::Clamp(InYear, 0, MAX_YEAR);
	Month = FMath::Clamp(InMonth, 0, MAX_MONTH);
	Day = FMath::Clamp(InDay, 0, MAXDAY_OF_MONTH[InMonth]);
	Hour = FMath::Clamp(InHour, 0, MAX_HOUR - 1);
	Minute = FMath::Clamp(InMinute, 0, MAX_MINUTE - 1);
}

FGameDateTime FGameDateTime::operator+(const FGameDateTime& rValue)
{
	int32 year = this->Year + rValue.Year;
	int32 month = this->Month + rValue.Month;
	int32 day = this->Day + rValue.Day;
	int32 hour = this->Hour + rValue.Hour;
	int32 minute = this->Minute + rValue.Minute;

	//FIngameTime의 값은 음수를 허용하지 않을 것이므로
	//+의 결과가 음수면 오버플로의 가능성이 있음.
	if (year < 0 || month < 0 || day < 0 || hour < 0 || minute < 0)
	{
		return *this;
	}

	/*
	* 시, 분은 >= 조건 : 0 허용
	* 월, 일은 > 조건 : 0 비허용
	* 연도도 최대 상한치가 있지만, 그때까지 플레이하는 것이 현실적으로 불가능할 것.
	*/

	if (minute >= MAX_MINUTE)
	{
		minute = minute % MAX_MINUTE;
		hour++;
	}

	if (hour >= MAX_HOUR)
	{
		hour = hour % MAX_HOUR;
		day++;
	}

	if (day > MAXDAY_OF_MONTH[month])
	{
		day = day % MAXDAY_OF_MONTH[month];
		month++;
	}

	if (month > MAX_MONTH)
	{
		month = month % MAX_MONTH;
		year++;
	}

	if (year > MAX_YEAR)
	{
		//Year Overflow!
		year = FMath::Clamp(year, 0, MAX_YEAR);
	}

	return FGameDateTime(year, month, day, hour, minute);
}

FGameDateTime& FGameDateTime::operator+=(const FGameDateTime& rValue)
{
	*this = *this + rValue;

	return *this;
}

FGameDateTime FGameDateTime::operator-(const FGameDateTime& rValue)
{
	int32 year = this->Year - rValue.Year;
	int32 month = this->Month - rValue.Month;
	int32 day = this->Day - rValue.Day;
	int32 hour = this->Hour - rValue.Hour;
	int32 minute = this->Minute - rValue.Minute;

	if (minute < 0)
	{
		minute = minute + MAX_MINUTE;
		hour--;
	}

	if (hour < 0)
	{
		hour = hour + MAX_HOUR;
		day--;
	}

	//day와 month는 0을 비허용함.

	if (day <= 0)
	{
		day = day + MAXDAY_OF_MONTH[month];
		month--;
	}

	if (month <= 0)
	{
		month = month + MAX_MONTH;
		year--;
	}

	if (year < 0)
	{
		//Year is Under 0
		year = FMath::Clamp(year, 0, MAX_YEAR);
	}

	return FGameDateTime(year, month, day, hour, minute);
}

FGameDateTime& FGameDateTime::operator-=(const FGameDateTime& rValue)
{
	*this = *this - rValue;

	return *this;
}

bool FGameDateTime::operator>(const FGameDateTime& Other) const
{
	// 연 월 일에 0값이 있다면, 해당 값으로 비교하기가 싫다는 의미임.

	if ((this->Year == 0 || Other.Year == 0) && (this->Month == 0 || Other.Month == 0) && (this->Day == 0 || Other.Day == 0))
	{
		//Year와 Month, Day가 유효하지 않음.
		//시 , 분 만으로 비교함.

		return	(this->Hour > Other.Hour) ||
			(this->Hour == Other.Hour && this->Minute > Other.Minute);
	}
	else if ((this->Year == 0 || Other.Year == 0) && (this->Month == 0 || Other.Month == 0))
	{
		//Year와 Month가 유효하지 않음.
		//일, 시 , 분 만으로 비교함.

		return (this->Day > Other.Day) ||
			(this->Day == Other.Day && this->Hour > Other.Hour) ||
			(this->Day == Other.Day && this->Hour == Other.Hour && this->Minute > Other.Minute);
	}
	else if ((this->Year == 0 || Other.Year == 0))
	{
		//Year가 유효하지 않음
		//월 일 시 분 으로 비교

		return (this->Month > Other.Month) ||
			(this->Month == Other.Month && this->Day > Other.Day) ||
			(this->Month == Other.Month && this->Day == Other.Day && this->Hour > Other.Hour) ||
			(this->Month == Other.Month && this->Day == Other.Day && this->Hour == Other.Hour && this->Minute > Other.Minute);
	}

	//모든 값이 유효함.
	//년 월 일 시 분 비교
	return this->Year> Other.Year ||
		(this->Year == Other.Year && this->Month > Other.Month) ||
		(this->Year == Other.Year && this->Month == Other.Month && this->Day > Other.Day) ||
		(this->Year == Other.Year && this->Month == Other.Month && this->Day == Other.Day && this->Hour > Other.Hour) ||
		(this->Year == Other.Year && this->Month == Other.Month && this->Day == Other.Day && this->Hour == Other.Hour && this->Minute > Other.Minute);
}

bool FGameDateTime::operator>=(const FGameDateTime& Other) const
{
	// 연 월 일에 0값이 있다면, 해당 값으로 비교하기가 싫다는 의미임.

	if ((this->Year == 0 || Other.Year == 0) && (this->Month == 0 || Other.Month == 0) && (this->Day == 0 || Other.Day == 0))
	{
		//Year와 Month, Day가 유효하지 않음.
		//시 , 분 만으로 비교함.

		return	(this->Hour >= Other.Hour) ||
			(this->Hour == Other.Hour && this->Minute >= Other.Minute);
	}
	else if ((this->Year == 0 || Other.Year == 0) && (this->Month == 0 || Other.Month == 0))
	{
		//Year와 Month가 유효하지 않음.
		//일, 시 , 분 만으로 비교함.

		return (this->Day >= Other.Day) ||
			(this->Day == Other.Day && this->Hour >= Other.Hour) ||
			(this->Day == Other.Day && this->Hour == Other.Hour && this->Minute >= Other.Minute);
	}
	else if ((this->Year == 0 || Other.Year == 0))
	{
		//Year가 유효하지 않음
		//월 일 시 분 으로 비교

		return (this->Month >= Other.Month) ||
			(this->Month == Other.Month && this->Day >= Other.Day) ||
			(this->Month == Other.Month && this->Day == Other.Day && this->Hour >= Other.Hour) ||
			(this->Month == Other.Month && this->Day == Other.Day && this->Hour == Other.Hour && this->Minute >= Other.Minute);
	}

	//모든 값이 유효함.
	//년 월 일 시 분 비교
	return this->Year >= Other.Year ||
		(this->Year == Other.Year && this->Month >= Other.Month) ||
		(this->Year == Other.Year && this->Month == Other.Month && this->Day >= Other.Day) ||
		(this->Year == Other.Year && this->Month == Other.Month && this->Day == Other.Day && this->Hour >= Other.Hour) ||
		(this->Year == Other.Year && this->Month == Other.Month && this->Day == Other.Day && this->Hour == Other.Hour && this->Minute >= Other.Minute);
}

bool FGameDateTime::operator<(const FGameDateTime& Other) const
{
	// 연 월 일에 0값이 있다면, 해당 값으로 비교하기가 싫다는 의미임.

	if ((this->Year == 0 || Other.Year == 0) && (this->Month == 0 || Other.Month == 0) && (this->Day == 0 || Other.Day == 0))
	{
		//Year와 Month, Day가 유효하지 않음.
		//시 , 분 만으로 비교함.

		return	(this->Hour < Other.Hour) ||
			(this->Hour == Other.Hour && this->Minute < Other.Minute);
	}
	else if ((this->Year == 0 || Other.Year == 0) && (this->Month == 0 || Other.Month == 0))
	{
		//Year와 Month가 유효하지 않음.
		//일, 시 , 분 만으로 비교함.

		return (this->Day < Other.Day) ||
			(this->Day == Other.Day && this->Hour < Other.Hour) ||
			(this->Day == Other.Day && this->Hour == Other.Hour && this->Minute < Other.Minute);
	}
	else if ((this->Year == 0 || Other.Year == 0))
	{
		//Year가 유효하지 않음
		//월 일 시 분 으로 비교

		return (this->Month < Other.Month) ||
			(this->Month == Other.Month && this->Day < Other.Day) ||
			(this->Month == Other.Month && this->Day == Other.Day && this->Hour < Other.Hour) ||
			(this->Month == Other.Month && this->Day == Other.Day && this->Hour == Other.Hour && this->Minute < Other.Minute);
	}

	//모든 값이 유효함.
	//년 월 일 시 분 비교
	return this->Year < Other.Year ||
		(this->Year == Other.Year && this->Month < Other.Month) ||
		(this->Year == Other.Year && this->Month == Other.Month && this->Day < Other.Day) ||
		(this->Year == Other.Year && this->Month == Other.Month && this->Day == Other.Day && this->Hour < Other.Hour) ||
		(this->Year == Other.Year && this->Month == Other.Month && this->Day == Other.Day && this->Hour == Other.Hour && this->Minute < Other.Minute);
}

bool FGameDateTime::operator<=(const FGameDateTime& Other) const
{
	// 연 월 일에 0값이 있다면, 해당 값으로 비교하기가 싫다는 의미임.

	if ((this->Year == 0 || Other.Year == 0) && (this->Month == 0 || Other.Month == 0) && (this->Day == 0 || Other.Day == 0))
	{
		//Year와 Month, Day가 유효하지 않음.
		//시 , 분 만으로 비교함.

		return	(this->Hour <= Other.Hour) ||
			(this->Hour == Other.Hour && this->Minute <= Other.Minute);
	}
	else if ((this->Year == 0 || Other.Year == 0) && (this->Month == 0 || Other.Month == 0))
	{
		//Year와 Month가 유효하지 않음.
		//일, 시 , 분 만으로 비교함.

		return (this->Day <= Other.Day) ||
			(this->Day == Other.Day && this->Hour <= Other.Hour) ||
			(this->Day == Other.Day && this->Hour == Other.Hour && this->Minute <= Other.Minute);
	}
	else if ((this->Year == 0 || Other.Year == 0))
	{
		//Year가 유효하지 않음
		//월 일 시 분 으로 비교

		return (this->Month <= Other.Month) ||
			(this->Month == Other.Month && this->Day <= Other.Day) ||
			(this->Month == Other.Month && this->Day == Other.Day && this->Hour <= Other.Hour) ||
			(this->Month == Other.Month && this->Day == Other.Day && this->Hour == Other.Hour && this->Minute <= Other.Minute);
	}

	//모든 값이 유효함.
	//년 월 일 시 분 비교
	return this->Year <= Other.Year ||
		(this->Year == Other.Year && this->Month <= Other.Month) ||
		(this->Year == Other.Year && this->Month == Other.Month && this->Day <= Other.Day) ||
		(this->Year == Other.Year && this->Month == Other.Month && this->Day == Other.Day && this->Hour <= Other.Hour) ||
		(this->Year == Other.Year && this->Month == Other.Month && this->Day == Other.Day && this->Hour == Other.Hour && this->Minute <= Other.Minute);
}

FString FGameDateTime::ToString() const
{
	return FString::Printf(TEXT("| Year : %d -- Month : %d -- Day : %d -- Hour : %d -- Minute : %d |"), Year, Month, Day, Hour, Minute);
}

EDayType FGameDateTime::GetDayType() const
{
	//0sus 3월 1일은 일요일이다. 그 기준부터 요일을 계산함.

	//1->0 - sunday
	//2->1 - monday
	//...
	//7->6 - saturday
	int sumDay = GetSumDay();
	EDayType result = EDayType(sumDay % 7);

	return result;
}

int32 FGameDateTime::GetSumDay() const
{
	//0년 3월 1일 기준으로 얼마나 지났는가?
	FGameDateTime current = *this;
	FGameDateTime compareTime = FGameDateTime(0, 3, 1);
	
	//FGameDateTime의 + - 계산은 day와 month를 0을 허용하지 않기 때문에 따로 계산함.
	
	int32 year = current.Year - compareTime.Year;
	int32 month = current.Month - compareTime.Month;
	
	//month가 음수라면 year에서 값을 1번 얻어 다시 계산한다.
	if (month < 0)
	{
		year--;
		month += 12;
	}
	int32 day = current.Day - compareTime.Day;

	//3월부터 시작함 : 3 4 5 6 7 8 9 10 11 12 1 2
	TArray<int32> months = { 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31, 28 };

	int32 monthSum = 0;
	for (int i = 0; i < month; i++) // 3월이면 1월 2월까지만 더한다.
	{
		monthSum += months[i];
	}

	int32 yearSum = 365; // year값 전부 합치면 무조건 365일임. 게임에선 윤년은 감안하지 않음.
	int32 yearToDay = yearSum * year;
	
	int32 total = yearToDay + monthSum + day;


	return total;
}

//~~

FCropSheetData::FCropSheetData() :MaxGrowth(0),Mesh0(nullptr), Mesh1(nullptr), Mesh2(nullptr), Mesh3(nullptr)
{
}

bool FCropSheetData::IsEmpty()
{
	//MaxGrowth가 0이거나 Mesh가 nullptr이면 빈 값으로 취급함.
	return (MaxGrowth == 0) ||!Mesh0|| !Mesh1 || !Mesh2 || !Mesh3;
}
