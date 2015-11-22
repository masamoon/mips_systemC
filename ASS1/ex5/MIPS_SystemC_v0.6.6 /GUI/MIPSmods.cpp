// MIPSmods.cpp


#include "../mips.h"
#include "modview.h"

#include "MIPSmods.h"
//Added by qt3to4:
#include <QPixmap>
#include <QCloseEvent>

#define MODSTEPX 160   // horizontal spacing of module views

/**
 * MIPSmods contructor.
 * Creates and inicializes the widgets that display the
 * port values of intruction memory, control, decode, register file,
 * alu and data memory.
 */
MIPSmods::MIPSmods( mips &m, QWidget* parent,  const char* name, Qt::WFlags fl )
    : Q3ScrollView( parent, name, fl ), mips1(m)
{   
    //resize viewport
    resizeContents(820+5,194+5);

    resize( QSize(1900+10,250+10) ); 
    setMaximumSize( QSize(1900+10,250+10) ); 

    setIcon(QPixmap("mips.xpm"));

    setVScrollBarMode(Auto);
    setHScrollBarMode(Auto);

    //imemview
    ModView *imemView=new ModView("imem",viewport());
    imemView->addPort(mips1.instmem->addr, "PC");
    imemView->addPort(mips1.instmem->inst, "inst");
    addChild(imemView,5,5);
    
    connect(this,SIGNAL(updateModules()), imemView, SLOT(redrawModule()));

    //ctrlview
    ModView *ctrlView=new ModView("Control",viewport());
    ctrlView->addPort(mips1.ctrl->opcode,  "opcode");
    ctrlView->addPort(mips1.ctrl->funct,   "funct");
    ctrlView->addPort(mips1.ctrl->RegDst,  "RegDst");
   // ctrlView->addPort(mips1.ctrl->Branch,  "Branch");
    ctrlView->addPort(mips1.ctrl->MemRead, "MemRead");
    ctrlView->addPort(mips1.ctrl->MemWrite,"MemWrite");
    ctrlView->addPort(mips1.ctrl->MemtoReg,"MemtoReg");
    ctrlView->addPort(mips1.ctrl->ALUSrc,  "ALUSrc");
    ctrlView->addPort(mips1.ctrl->ALUOp,   "ALUOp");
    ctrlView->addPort(mips1.ctrl->RegWrite,"RegWrite");
    ctrlView->addPort(mips1.ctrl->jbr,"jbr");
    addChild(ctrlView,5+MODSTEPX*1,5);
    
    connect(this,SIGNAL(updateModules()), ctrlView, SLOT(redrawModule()));

    //rfileview
    ModView *rfileView=new ModView("regfile",viewport());
    rfileView->addPort(mips1.rfile->reg1, "r1");
    rfileView->addPort(mips1.rfile->reg2, "r2");
    rfileView->addPort(mips1.rfile->regwrite, "rw");
    rfileView->addPort(mips1.rfile->data1, "r1_out");
    rfileView->addPort(mips1.rfile->data2, "r2_out");
    rfileView->addPort(mips1.rfile->datawr, "rw_in");
    addChild(rfileView,5+MODSTEPX*2,5);
    
    connect(this,SIGNAL(updateModules()), rfileView, SLOT(redrawModule()));

    //aluView
    ModView *aluView=new ModView("ALU",viewport());
    aluView->addPort(mips1.alu1->din1, "din1");
    aluView->addPort(mips1.alu1->din2, "din2");
    aluView->addPort(mips1.alu1->op, "op");
    aluView->addPort(mips1.alu1->dout, "dout");
   // aluView->addPort(mips1.alu1->zero, "zero");
    addChild(aluView,5+MODSTEPX*3,5);

    connect(this,SIGNAL(updateModules()), aluView, SLOT(redrawModule()));

    //dmemview
    ModView *dmemView=new ModView("dmem",viewport());
    dmemView->addPort(mips1.datamem->addr, "addr");
    dmemView->addPort(mips1.datamem->din, "din");
    dmemView->addPort(mips1.datamem->dout, "dout");
    addChild(dmemView,5+MODSTEPX*4,5);
    
    connect(this,SIGNAL(updateModules()), dmemView, SLOT(redrawModule()));

    //hazview
    ModView *hazview=new ModView("haz",viewport());
    hazview->addPort(mips1.hazard_unit->rs, "rs");
    hazview->addPort(mips1.hazard_unit->rt, "rt");
    //hazview->addPort(mips1.hazard_unit->MemRead_exe, "MRead_e");
    //hazview->addPort(mips1.hazard_unit->MemRead_mem, "MRead_m");
    hazview->addPort(mips1.hazard_unit->MemRead, "MRead");
    hazview->addPort(mips1.hazard_unit->jbr, "jbr"); 
    hazview->addPort(mips1.hazard_unit->WriteReg_exe, "WrReg_e");
    hazview->addPort(mips1.hazard_unit->WriteReg_mem, "WrReg_m");
    hazview->addPort(mips1.hazard_unit->RegWrite_exe, "RWrite_e");
    hazview->addPort(mips1.hazard_unit->RegWrite_mem, "RWrite_m");
    hazview->addPort(mips1.hazard_unit->BranchTaken, "BrTken"); 
    hazview->addPort(mips1.hazard_unit->enable_pc, "en_pc");
    hazview->addPort(mips1.hazard_unit->enable_ifid, "en_ifid");
    hazview->addPort(mips1.hazard_unit->enable_id1id2, "en_id1id2");
    hazview->addPort(mips1.hazard_unit->reset_id1id2, "rs_id1id2");
    hazview->addPort(mips1.hazard_unit->reset_idexe, "rs_idexe");
    hazview->addPort(mips1.hazard_unit->reset_ifid, "rs_ifid");
    hazview->addPort(mips1.hazard_unit->reset_exmem, "rs_exmem");

    addChild(hazview,5+MODSTEPX*5,5);
    
    connect(this,SIGNAL(updateModules()), hazview, SLOT(redrawModule()));



    //fwdview
    ModView *fwdview=new ModView("forward",viewport());
    fwdview->addPort(mips1.fwd->rs, "rs");
    fwdview->addPort(mips1.fwd->rt, "rt");
    fwdview->addPort(mips1.fwd->rs_id2,"rsid2");
    fwdview->addPort(mips1.fwd->rt_id2,"rtid2");
    fwdview->addPort(mips1.fwd->WriteReg_wb, "wrreg_wb");
    fwdview->addPort(mips1.fwd->MemRead, "MRead");
    fwdview->addPort(mips1.fwd->RegWrite_mem, "regwr_mem");
    fwdview->addPort(mips1.fwd->RegWrite_wb, "RegWr_wb");

    //fwdview->addPort(mips1.hazard_unit->WriteReg_exe, "WrReg_e");
    fwdview->addPort(mips1.fwd->WriteReg_mem, "WrReg_m");
    //fwdview->addPort(mips1.hazard_unit->RegWrite_exe, "RWrite_e");
    fwdview->addPort(mips1.fwd->mux_alu1, "mux1");
    fwdview->addPort(mips1.fwd->mux_alu2, "mux2"); 
    fwdview->addPort(mips1.fwd->mux_comp1_sel, "mc1");
    fwdview->addPort(mips1.fwd->mux_comp2_sel, "mc2"); 
    fwdview->addPort(mips1.fwd->jbr, "jbr");
    addChild(fwdview,5+MODSTEPX*7,5);
    
    connect(this,SIGNAL(updateModules()), fwdview, SLOT(redrawModule()));


    //muxalu2
    ModView *malu2view = new ModView("malu2",viewport());
    malu2view->addPort(mips1.m2alu->sel1,"sel1");
    malu2view->addPort(mips1.m2alu->sel2,"sel2");
    malu2view->addPort(mips1.m2alu->dout,"dout");
    
   
    addChild(malu2view,5+MODSTEPX*8,5);
    
    connect(this,SIGNAL(updateModules()), malu2view, SLOT(redrawModule()));
    
    //muxmem
/*    ModView *muxmemview = new ModView("mmem",viewport());
    muxmemview->addPort(mips1.memmux->din0, "din0");
    muxmemview->addPort(mips1.memmux->din1, "din1");
    muxmemview->addPort(mips1.memmux->sel, "sel"); 
    muxmemview->addPort(mips1.memmux->dout, "dout");

   addChild(muxmemview,5+MODSTEPX*9,5);
    
    connect(this,SIGNAL(updateModules()), muxmemview, SLOT(redrawModule()));
*/

    ModView *muxcomp1view = new ModView("mcomp1",viewport());
    muxcomp1view->addPort(mips1.muxcomp1->din0, "din0");
    muxcomp1view->addPort(mips1.muxcomp1->din1, "din1");
    muxcomp1view->addPort(mips1.muxcomp1->din2, "din2");	
    muxcomp1view->addPort(mips1.muxcomp1->sel, "sel"); 
    muxcomp1view->addPort(mips1.muxcomp1->dout, "dout");

   addChild(muxcomp1view,5+MODSTEPX*9,5);
    
    connect(this,SIGNAL(updateModules()), muxcomp1view, SLOT(redrawModule()));


    ModView *muxcomp2view = new ModView("mcomp2",viewport());
    muxcomp2view->addPort(mips1.muxcomp2->din0, "din0");
    muxcomp2view->addPort(mips1.muxcomp2->din1, "din1");
    muxcomp2view->addPort(mips1.muxcomp2->din2, "din2"); 
    muxcomp2view->addPort(mips1.muxcomp2->sel, "sel"); 
    muxcomp2view->addPort(mips1.muxcomp2->dout, "dout");

   addChild(muxcomp2view,5+MODSTEPX*11,5);
    
    connect(this,SIGNAL(updateModules()), muxcomp2view, SLOT(redrawModule()));



   //muxdmem
   ModView *muxdmemview = new ModView("dmemmu",viewport());
   muxdmemview->addPort(mips1.datamem_mux->din0, "din0");
   muxdmemview->addPort(mips1.datamem_mux->din1, "din1"); 
   muxdmemview->addPort(mips1.datamem_mux->sel, "sel"); 
   muxdmemview->addPort(mips1.datamem_mux->dout, "dout");

   addChild(muxdmemview,5+MODSTEPX*10,5);
    
    connect(this,SIGNAL(updateModules()), muxdmemview, SLOT(redrawModule()));


    ModView *ctrl2view =new ModView("ctrl2",viewport());
    ctrl2view->addPort(mips1.ctrl2->le, "le");
    ctrl2view->addPort(mips1.ctrl2->gr, "gr");
    ctrl2view->addPort(mips1.ctrl2->eq, "eq");
    ctrl2view->addPort(mips1.ctrl2->select, "ctrl2_sel");
    ctrl2view->addPort(mips1.ctrl2->jbr, "jbr");
    ctrl2view->addPort(mips1.ctrl2->btaken, "btaken");

    addChild(ctrl2view,5+MODSTEPX*6,5);
    
    connect(this,SIGNAL(updateModules()), ctrl2view, SLOT(redrawModule()));

    setFocusPolicy(Qt::StrongFocus);
}

/*  
 *  Destroys the object and frees any allocated resources
 */
MIPSmods::~MIPSmods()
{
    // no need to delete child widgets, Qt does it all for us
}

void MIPSmods::closeEvent(QCloseEvent *e)
{
   e->ignore();  //dont close
}
