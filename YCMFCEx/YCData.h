#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif



//////////////////////////////////////////////////////////////////////////////
// CYCData
//
#define   VIRTUAL_CYCData_UpdateValid()                 virtual void UpdateValid()
#define IMPLEMENT_CYCData_UpdateValid(AClass)           void AClass::UpdateValid()
#define  OVERRIDE_CYCData_UpdateValid                   VIRTUAL_CYCData_UpdateValid


class CYCData : public CYCObject
{
    DECLARE_SERIAL(CYCData)

public:

    CYCData();


    // override
    OVERRIDE_CObject_Serialize();


    bool IsValid() const;
    void ResetValid();


protected:

    CYCData(const CYCData &ASrc);


    OVERRIDE_CYCObject_Assign();
    OVERRIDE_CYCObject_IsEqual();


    void SetValid();

    VIRTUAL_CYCData_UpdateValid();


private:

    bool m_IsValid;

};
//
// CYCData
//////////////////////////////////////////////////////////////////////////////
